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
#include <asm/arch/regs-dmc.h>

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

inline void writelrb(uint32_t val, uint32_t *addr)
{
	writel(val, (uint32_t)addr);
	asm volatile("" : : : "memory");
	readl((uint32_t)addr);
	asm volatile("" : : : "memory");
}

void pxa3xx_dram_init(void)
{
	struct pxa3xx_dmc_regs *regs = (struct pxa3xx_dmc_regs *)DMC_BASE;
	uint32_t mdcnfg = CONFIG_SYS_PXA3XX_DDR_MDCNFG;
	uint32_t tmp;

	mdcnfg &= (MDCNFG_DTC_MASK | MDCNFG_DRAC_MASK | MDCNFG_DCAC_MASK |
			MDCNFG_DBW | MDCNFG_DCSE1 | MDCNFG_DCSE0);
	mdcnfg |= 0x80000400;	/* SETALWAYS bits */

	/* 1.8.1 -- 2. Program DTC, DRAC, DCAC */
	writelrb(mdcnfg & ~(MDCNFG_DCSE1 | MDCNFG_DCSE0), &regs->mdcnfg);

	/* 1.8.1 -- 3. Program DCSE */
	writelrb(mdcnfg, &regs->mdcnfg);

	/* 1.8.1 -- 5a. Enable RCOMP interrupt (we disable it) */
	writelrb(0, &regs->dmcier);

	/* 1.8.1 -- 5b. SWEVAL, RCRNG, REI (5c., 5d.) */
	writelrb(RCOMP_SWEVAL | (1 << 24) |	/* SETALWAYS bit */
		(CONFIG_SYS_PXA3XX_DDR_RCRNG << RCOMP_RCRNG_OFFSET) |
		(CONFIG_SYS_PXA3XX_DDR_REI << RCOMP_REI_OFFSET),
		&regs->rcomp);

	/* 1.8.1 -- 5e. Wait for RCI, then clear it */
	while (!(readl(&regs->dmcisr) & DMCISR_RCI))
		;
	writel(DMCISR_RCI, &regs->dmcisr);

	/* 1.8.1 -- 5f. ??? REVISIT */

	/* 1.8.1 -- 5g. RCOMP UPDATE */
	tmp = readl(&regs->rcomp);
	tmp |= RCOMP_UPDATE;
	writel(tmp, &regs->rcomp);

	/* 1.8.1 -- 5h. Wait for RCOMP UPDATE cleared */
	while (readl(&regs->rcomp) & RCOMP_UPDATE)
		;

	/* 1.8.1 -- 6b. Clear HCRNG, HCOFF (6c.) */
	tmp = readl(&regs->ddr_hcal);
	tmp &= ~(DDR_HCAL_HCOFF1_MASK | DDR_HCAL_HCOFF0_MASK |
			DDR_HCAL_HCRNG_MASK);
	writelrb(tmp, &regs->ddr_hcal);

	/* 1.8.1 -- 6d. Clear WCEN, WCOFF (6e.) */
	tmp = readl(&regs->ddr_wcal);
	tmp &= ~(DDR_WCAL_WCEN | DDR_WCAL_WCOFF_MASK);
	writelrb(tmp, &regs->ddr_wcal);

	/* 1.8.1 -- 6f. Set HCEN */
	tmp = readl(&regs->ddr_hcal);
	tmp |= DDR_HCAL_HCEN;
	writelrb(tmp, &regs->ddr_hcal);

	/* 1.8.1 -- 6g. Set HCPROG */
	tmp = readl(&regs->ddr_hcal);
	tmp |= DDR_HCAL_HCPROG;
	writelrb(tmp, &regs->ddr_hcal);

	/* 1.8.1 -- 6h. Set HWFREQ */
	tmp = readl(&regs->mdcnfg);
	tmp |= MDCNFG_HWFREQ;
	writelrb(tmp, &regs->mdcnfg);

	/* 1.8.1 -- 7. Write MDMRS */
	tmp = MDMRS_MDPEND | CONFIG_SYS_PXA3XX_DDR_MDMRS;
	tmp |= (mdcnfg & (MDCNFG_DCSE1 | MDCNFG_DCSE0)) << MDMRS_MDCS0_OFFSET;
	writelrb(tmp, &regs->mdmrs);

	/* 1.8.1 -- 8. Write MDREFR */
	writelrb(0x1e, &regs->mdrefr);

	/* 1.8.1 -- 9. Program HCRNG > 0 */
	tmp = readl(&regs->ddr_hcal);
	tmp |= 1 << 27;		/* SETALWAYS bit */
	tmp |= 2 << DDR_HCAL_HCRNG_OFFSET;
	writelrb(tmp, &regs->ddr_hcal);

	/* 1.8.1 -- 10. Program DMCEN, Enable DMC */
	tmp = readl(&regs->mdcnfg);
	tmp |= MDCNFG_DMCEN;
	writelrb(tmp, &regs->mdcnfg);
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
