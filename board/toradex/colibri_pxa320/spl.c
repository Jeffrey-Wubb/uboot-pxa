/*
 * Toradex Colibri PXA320 NAND SPL
 *
 * Copyright (C) 2011 Marek Vasut <marek.vasut@gmail.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <config.h>
#include <asm/io.h>
#include <asm/arch/pxa.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <nand.h>
#include <asm-generic/gpio.h>
#include <asm/arch/pxa-regs.h>
#include <asm/arch/regs-gpio.h>

#include "colibri_pxa320.h"

DECLARE_GLOBAL_DATA_PTR;

#define	CPLD_REG_CS_CTRL			0x17800000
#define	CPLD_REG_CS_CTRL_EXT_nCS0_EN		(1 << 0)
#define	CPLD_REG_CS_CTRL_EXT_nCS1_EN		(1 << 1)
#define	CPLD_REG_CS_CTRL_EXT_nCS2_EN		(1 << 2)
#define	CPLD_REG_CS_CTRL_EXT_nCS0_EC_EN		(1 << 5)
#define	CPLD_REG_CS_CTRL_EXT_nCS1_EC_EN		(1 << 6)
#define	CPLD_REG_CS_CTRL_EXT_nCS2_EC_EN		(1 << 7)
#define	CPLD_REG_CS_CTRL_EXT_nCS0_DIS		(1 << 8)
#define	CPLD_REG_CS_CTRL_EXT_nCS1_DIS		(1 << 9)
#define	CPLD_REG_CS_CTRL_EXT_nCS2_DIS		(1 << 10)
#define	CPLD_REG_CS_CTRL_EXT_nCS0_EC_DIS	(1 << 11)
#define	CPLD_REG_CS_CTRL_EXT_nCS1_EC_DIS	(1 << 12)
#define	CPLD_REG_CS_CTRL_EXT_nCS2_EC_DIS	(1 << 13)

#define	CPLD_REG_CS_MEM				0x17800004
#define	CPLD_REG_CS_MEM_CF_EN			(1 << 0)
#define	CPLD_REG_CS_MEM_RDnWR_EN		(1 << 1)
#define	CPLD_REG_CS_MEM_nOE_EN			(1 << 2)
#define	CPLD_REG_CS_MEM_CF_DIS			(1 << 8)
#define	CPLD_REG_CS_MEM_RDnWR_DIS		(1 << 9)
#define	CPLD_REG_CS_MEM_nOE_DIS			(1 << 10)

void board_init_f(unsigned long unused)
{
	extern uint32_t __bss_start, __bss_end__;

	struct nand_chip nand_chip;
	nand_info_t mtd;
	uint32_t page, start_page, end_page;
	uint32_t dest = CONFIG_SYS_NAND_U_BOOT_DST;

	writel(0x028ff21f, 0x41340000);
	asm volatile("mcr p14, 0, %0, c6, c0, 0"::"r"(2));
	while (((readl(0x41340004) >> 28) & 0x3) != 0x3);

	/* Pointer is writable since we allocated a register for it. */
	gd = (gd_t *) ((CONFIG_SYS_INIT_SP_ADDR) & ~0x07);
	/* Compiler optimization barrier needed for GCC >= 3.4. */
	__asm__ __volatile__("": : :"memory");
	/* Wipe the GD. */
	memset((void *)gd, 0, sizeof(gd_t));
	/* Wipe the BSS. */
	memset(&__bss_start, 0, &__bss_end__ - &__bss_start);

	timer_init();

	pxa3xx_dram_init();

	/* Setup the GPIO, CS etc. */
	board_init_common();

	/* Copy the U-Boot from NAND to DRAM. */
	mtd.priv = &nand_chip;
	board_nand_init(&nand_chip);
	nand_scan(&mtd, CONFIG_SYS_NAND_MAX_CHIPS);

	start_page = CONFIG_SYS_NAND_U_BOOT_OFFS / mtd.writesize;
	end_page = start_page + CONFIG_SYS_NAND_U_BOOT_SIZE / mtd.writesize;

	nand_chip.cmdfunc(&mtd, NAND_CMD_RESET, 0, 0);

	for (page = start_page ; page < end_page ; page++) {
		nand_chip.cmdfunc(&mtd, NAND_CMD_READ0, 0, page);
		nand_chip.read_buf(&mtd, (uint8_t *)dest, mtd.writesize);
		dest += mtd.writesize;
	}

	asm volatile("mov pc, %0\n"::"r"(CONFIG_SYS_NAND_U_BOOT_DST));

	for (;;)
		;
}

void __attribute__((noreturn)) hang(void)
{
	for (;;)
		;
}

void icache_disable(void) {}
void dcache_disable(void) {}
void serial_putc(const char c) {}
void serial_puts(const char *s) {}

int do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	return 0;
}
