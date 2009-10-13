/*
 * Toradex Colibri PXA320 support file
 *
 * Copyright (C) 2009 Marek Vasut <marek.vasut@gmail.com>
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
#include <asm/arch/pxa-regs.h>
#include <asm/arch/regs-mmc.h>
#include <asm/io.h>

#include "colibri_pxa320.h"

DECLARE_GLOBAL_DATA_PTR;

/*
 * Miscelaneous platform dependent initialisations
 */

int board_init (void)
{
	/* arch number for linux kernel */
	gd->bd->bi_arch_number = MACH_TYPE_COLIBRI320;

	/* adress of boot parameters */
	gd->bd->bi_boot_params = 0xa0000100;

	board_init_common();

	return 0;
}

int dram_init(void)
{
	gd->ram_size = PHYS_SDRAM_1_SIZE;
	return 0;
}

#ifdef	CONFIG_CMD_USB
int usb_board_init(void)
{
	writel((readl(UHCHR) | UHCHR_PCPL | UHCHR_PSPL) &
		~(UHCHR_SSEP0 | UHCHR_SSEP1 | UHCHR_SSEP2 | UHCHR_SSE),
		UHCHR);

	writel(readl(UHCHR) | UHCHR_FSBIR, UHCHR);

	while (UHCHR & UHCHR_FSBIR);

	writel(readl(UHCHR) & ~UHCHR_SSE, UHCHR);
	writel((UHCHIE_UPRIE | UHCHIE_RWIE), UHCHIE);

	writel(readl(UHCRHDA) & ~(0x200), UHCRHDA);
	writel(readl(UHCRHDA) | 0x100, UHCRHDA);

	/* Set port power control mask bits, only 3 ports. */
	writel(readl(UHCRHDB) | (0x7<<17), UHCRHDB);

	/* enable port 2 */
	writel(readl(UP2OCR) | UP2OCR_HXOE | UP2OCR_HXS |
		UP2OCR_DMPDE | UP2OCR_DPPDE, UP2OCR);

	return 0;
}

void usb_board_init_fail(void)
{
	return;
}

void usb_board_stop(void)
{
	writel(readl(UHCHR) | UHCHR_FHR, UHCHR);
	udelay(11);
	writel(readl(UHCHR) & ~UHCHR_FHR, UHCHR);

	writel(readl(UHCCOMS) | 1, UHCCOMS);
	udelay(10);

//	writel(readl(CKEN) & ~CKEN10_USBHOST, CKEN);

	return;
}
#endif

#ifdef	CONFIG_CMD_MMC
int board_mmc_init(bd_t *bis)
{
	pxa_mmc_register(0);
	return 0;
}
#endif

ulong get_tbclk(void)
{
	return CONFIG_SYS_HZ;
}
/*
void mtd_erase_callback(struct erase_info *instr)
{
	if (instr->callback)
		instr->callback(instr);
}*/
