/*
 * Marvell PXA3xx init code
 *
 * Copyright (C) 2011 Marek Vasut <marek.vasut@gmail.com>
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

#include <asm/io.h>
#include <asm/system.h>
#include <command.h>
#include <common.h>
#include <asm/arch/pxa-regs.h>

/* Flush I/D-cache */
static void cache_flush(void)
{
	unsigned long i = 0;

	asm ("mcr p15, 0, %0, c7, c5, 0" : : "r" (i));
}

int cleanup_before_linux(void)
{
	/*
	 * This function is called just before we call Linux. It prepares
	 * the processor for Linux by just disabling everything that can
	 * disturb booting Linux.
	 */

	disable_interrupts();
	icache_disable();
	dcache_disable();
	cache_flush();

	return 0;
}

int arch_cpu_init(void)
{
	return 0;
}

void i2c_clk_enable(void)
{
	/* Set the global I2C clock on */
	writel(readl(CKENB) | CKENB_4_I2C, CKENB);
}

void reset_cpu(ulong ignored) __attribute__((noreturn));

void reset_cpu(ulong ignored)
{
	uint32_t tmp;

	setbits_le32(OWER, OWER_WME);

	tmp = readl(OSCR);
	tmp += 0x1000;
	writel(tmp, OSMR3);

	for (;;)
		;
}
