/*
 * Toradex Colibri PXA320 common init code
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
#include <nand.h>
#include <asm-generic/gpio.h>
#include <asm/arch/pxa-regs.h>
#include <asm/arch/regs-gpio.h>

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

void board_init_common(void)
{
	struct pxa320_mfpr_regs *mfpr_regs =
		(struct pxa320_mfpr_regs *)MFPR_BASE;

	const uint32_t uart_mfpr =
		MFPR_DRIVE_FAST_3MA | (1 << MFPR_AF_SEL_OFFSET);
	const uint32_t mmc_mfpr =
		MFPR_DRIVE_FAST_3MA | (4 << MFPR_AF_SEL_OFFSET);
	const uint32_t cpld_mfpr =
		MFPR_PULL_SEL | MFPR_PULLUP_EN | MFPR_PULLDOWN_EN |
		MFPR_DRIVE_FAST_3MA | (0 << MFPR_AF_SEL_OFFSET);

	writel(uart_mfpr, &mfpr_regs->gpio97);
	writel(uart_mfpr, &mfpr_regs->gpio98);
	writel(uart_mfpr, &mfpr_regs->gpio99);
	writel(uart_mfpr, &mfpr_regs->gpio100);
	writel(uart_mfpr, &mfpr_regs->gpio101);
	writel(uart_mfpr, &mfpr_regs->gpio102);
	writel(uart_mfpr, &mfpr_regs->gpio103);
	writel(uart_mfpr, &mfpr_regs->gpio104);

	/* Enable NAND flash clock */
	writel(readl(CKENA) | CKENA_4_NAND, CKENA);

	/* Ethernet chip configuration */
	writel(uart_mfpr, &mfpr_regs->gpio3);
	writel(0x7ff8023c, MSC1);
	writel(0x0032c80b, CSADRCFG2);

	/* Chipselect 3 configuration */
	writel(uart_mfpr, &mfpr_regs->gpio4);
	writel(0x0032c809, CSADRCFG3);

	/* Configuration for Compact Flash */
	writel(0x0038080c, CSADRCFG_P);
	writel(0x00000002, CSMSADRCFG);

	/* Configuration for the CPLD */
#if 0	/* Disabled due to bug in CPLD FW v1.6 */
	writew (CPLD_REG_CS_CTRL_EXT_nCS0_EN |
		CPLD_REG_CS_CTRL_EXT_nCS1_EN |
		CPLD_REG_CS_CTRL_EXT_nCS2_EN,
		CPLD_REG_CS_CTRL);
#endif
	writew(CPLD_REG_CS_MEM_CF_EN |
		CPLD_REG_CS_MEM_RDnWR_EN |
		CPLD_REG_CS_MEM_nOE_EN,
		CPLD_REG_CS_MEM);

	/* CPLD programming interface */
	writel(cpld_mfpr | (7 << MFPR_AF_SEL_OFFSET), &mfpr_regs->gpio1);
	writel(cpld_mfpr, &mfpr_regs->gpio1_2);
	writel(cpld_mfpr, &mfpr_regs->gpio83);
	writel(cpld_mfpr, &mfpr_regs->gpio85);
	writel(cpld_mfpr, &mfpr_regs->gpio86);

	gpio_direction_output(2, 0);

	gpio_direction_output(83, 0);
	gpio_direction_output(86, 0);
	gpio_direction_input(85);

	/* MMC */
	writel(mmc_mfpr, &mfpr_regs->gpio18);
	writel(mmc_mfpr, &mfpr_regs->gpio19);
	writel(mmc_mfpr, &mfpr_regs->gpio20);
	writel(mmc_mfpr, &mfpr_regs->gpio21);
	writel(mmc_mfpr, &mfpr_regs->gpio22);
	writel(mmc_mfpr, &mfpr_regs->gpio23);
}
