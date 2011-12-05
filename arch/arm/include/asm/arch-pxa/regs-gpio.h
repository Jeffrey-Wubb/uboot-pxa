/*
 * PXA GPIO and MFPR register definitions
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

#ifndef	__REGS_GPIO_H__
#define	__REGS_GPIO_H__

#define GPIO_BASE	0x40e00000
#define MFPR_BASE	0x40e10000

struct pxa300_mfpr_regs {
	uint32_t	reserved0[45];

	uint32_t	gpio0;
	uint32_t	gpio1;
	uint32_t	gpio2;
	uint32_t	n_cs1;
	uint32_t	n_cs0;
	uint32_t	df_int_rnb;
	uint32_t	df_nwe;

	uint32_t	reserved1[76];

	uint32_t	df_nre;
	uint32_t	n_be0;
	uint32_t	n_be1;
	uint32_t	df_ale_nwe;
	uint32_t	df_addr0;
	uint32_t	df_addr1;
	uint32_t	df_addr2;
	uint32_t	df_addr3;
	uint32_t	df_io0;
	uint32_t	df_io8;
	uint32_t	df_io1;
	uint32_t	df_io9;
	uint32_t	df_io2;
	uint32_t	df_io10;
	uint32_t	df_io3;
	uint32_t	df_io11;
	uint32_t	df_cle_noe;
	uint32_t	n_lua;
	uint32_t	df_ncs0;

	uint32_t	reserved2;

	uint32_t	df_sclk_e;
	uint32_t	n_lla;
	uint32_t	df_io4;
	uint32_t	df_io12;
	uint32_t	df_io5;
	uint32_t	df_io13;
	uint32_t	df_io6;
	uint32_t	df_io14;
	uint32_t	df_io7;
	uint32_t	df_io15;
	uint32_t	df_ncs1;
	uint32_t	gpio3;
	uint32_t	gpio4;
	uint32_t	gpio5;
	uint32_t	gpio6;
	uint32_t	gpio7;
	uint32_t	gpio8;
	uint32_t	gpio9;
	uint32_t	gpio10;
	uint32_t	gpio11;
	uint32_t	gpio12;
	uint32_t	gpio13;
	uint32_t	gpio14;
	uint32_t	gpio15;
	uint32_t	gpio16;
	uint32_t	gpio17;
	uint32_t	gpio18;
	uint32_t	gpio19;
	uint32_t	gpio20;
	uint32_t	gpio21;
	uint32_t	gpio22;
	uint32_t	gpio23;
	uint32_t	gpio24;
	uint32_t	gpio25;
	uint32_t	gpio26;
	uint32_t	gpio2_2;
	uint32_t	gpio3_2;
	uint32_t	gpio4_2;
	uint32_t	gpio5_2;
	uint32_t	gpio6_2;

	uint32_t	reserved3[68];

	uint32_t	gpio27;
	uint32_t	gpio28;
	uint32_t	gpio29;
	uint32_t	ulpi_stp;
	uint32_t	ulpi_nxt;
	uint32_t	ulpi_dir;
	uint32_t	gpio30;
	uint32_t	gpio31;
	uint32_t	gpio32;
	uint32_t	gpio33;
	uint32_t	gpio34;
	uint32_t	gpio35;
	uint32_t	gpio36;
	uint32_t	gpio37;
	uint32_t	gpio38;
	uint32_t	gpio39;
	uint32_t	gpio40;
	uint32_t	gpio41;
	uint32_t	gpio42;
	uint32_t	gpio43;
	uint32_t	gpio44;
	uint32_t	gpio45;
	uint32_t	gpio46;
	uint32_t	gpio47;
	uint32_t	gpio48;
	uint32_t	gpio49;
	uint32_t	gpio50;
	uint32_t	gpio51;
	uint32_t	gpio52;
	uint32_t	gpio53;
	uint32_t	gpio54;
	uint32_t	gpio55;
	uint32_t	gpio56;
	uint32_t	gpio57;
	uint32_t	gpio58;
	uint32_t	gpio59;
	uint32_t	gpio60;
	uint32_t	gpio61;
	uint32_t	gpio62;
	uint32_t	gpio63;
	uint32_t	gpio64;
	uint32_t	gpio65;
	uint32_t	gpio66;
	uint32_t	gpio67;
	uint32_t	gpio68;
	uint32_t	gpio69;
	uint32_t	gpio70;
	uint32_t	gpio71;
	uint32_t	gpio72;
	uint32_t	gpio73;
	uint32_t	gpio74;
	uint32_t	gpio75;
	uint32_t	gpio76;
	uint32_t	gpio77;
	uint32_t	gpio78;
	uint32_t	gpio79;
	uint32_t	gpio80;
	uint32_t	gpio81;
	uint32_t	gpio82;
	uint32_t	gpio83;
	uint32_t	gpio84;
	uint32_t	gpio85;
	uint32_t	gpio86;
	uint32_t	gpio87;
	uint32_t	gpio88;
	uint32_t	gpio89;
	uint32_t	gpio90;
	uint32_t	gpio91;
	uint32_t	gpio92;
	uint32_t	gpio93;
	uint32_t	gpio94;
	uint32_t	gpio95;
	uint32_t	gpio96;
	uint32_t	gpio97;
	uint32_t	gpio98;

#ifdef CONFIG_CPU_PXA310
	uint32_t	gpio7_2;
	uint32_t	gpio8_2;
	uint32_t	gpio9_2;
	uint32_t	gpio10_2;

	uint32_t	reserved4[49];
#else
	uint32_t	reserved4[53];
#endif

	uint32_t	gpio99;
	uint32_t	gpio100;
	uint32_t	gpio101;
	uint32_t	gpio102;
	uint32_t	gpio103;
	uint32_t	gpio104;
	uint32_t	gpio105;
	uint32_t	gpio106;
	uint32_t	gpio107;
	uint32_t	gpio108;
	uint32_t	gpio109;
	uint32_t	gpio110;
	uint32_t	gpio111;
	uint32_t	gpio112;
	uint32_t	gpio113;
	uint32_t	gpio114;
	uint32_t	gpio115;
	uint32_t	gpio116;
	uint32_t	gpio117;
	uint32_t	gpio118;
	uint32_t	gpio119;
	uint32_t	gpio120;
	uint32_t	gpio121;
	uint32_t	gpio122;
	uint32_t	gpio123;
	uint32_t	gpio124;
	uint32_t	gpio125;
	uint32_t	gpio126;
	uint32_t	gpio127;
	uint32_t	gpio0_2;
	uint32_t	gpio1_2;
};

struct pxa320_mfpr_regs {
	uint32_t	reserved0[73];

	uint32_t	gpio0;
	uint32_t	gpio1;
	uint32_t	gpio2;
	uint32_t	gpio3;
	uint32_t	gpio4;
	uint32_t	n_xcvren;

	uint32_t	reserved1[50];

	uint32_t	df_cle_noe;
	uint32_t	df_ale_nwe1;

	uint32_t	reserved2;

	uint32_t	df_sclk_e;
	uint32_t	n_be0;
	uint32_t	nbe1;
	uint32_t	df_ale_nwe2;
	uint32_t	df_int_rnb;
	uint32_t	df_ncs0;
	uint32_t	df_ncs1;
	uint32_t	df_nwe;
	uint32_t	df_nre;
	uint32_t	n_lua;
	uint32_t	n_lla;
	uint32_t	df_addr0;
	uint32_t	df_addr1;
	uint32_t	df_addr2;
	uint32_t	df_addr3;
	uint32_t	df_io0;
	uint32_t	df_io8;
	uint32_t	df_io1;
	uint32_t	df_io9;
	uint32_t	df_io2;
	uint32_t	df_io10;
	uint32_t	df_io3;
	uint32_t	df_io11;
	uint32_t	df_io4;
	uint32_t	df_io12;
	uint32_t	df_io5;
	uint32_t	df_io13;
	uint32_t	df_io6;
	uint32_t	df_io14;
	uint32_t	df_io7;
	uint32_t	df_io15;
	uint32_t	gpio5;
	uint32_t	gpio6;
	uint32_t	gpio7;
	uint32_t	gpio8;
	uint32_t	gpio9;
	uint32_t	gpio11;
	uint32_t	gpio12;
	uint32_t	gpio13;
	uint32_t	gpio14;
	uint32_t	gpio15;
	uint32_t	gpio16;
	uint32_t	gpio17;
	uint32_t	gpio18;
	uint32_t	gpio19;
	uint32_t	gpio20;
	uint32_t	gpio21;
	uint32_t	gpio22;
	uint32_t	gpio23;
	uint32_t	gpio24;
	uint32_t	gpio25;
	uint32_t	gpio26;

	uint32_t	reserved3[72];

	uint32_t	gpio27;
	uint32_t	gpio28;
	uint32_t	gpio29;
	uint32_t	gpio30;
	uint32_t	gpio31;
	uint32_t	gpio32;
	uint32_t	gpio33;
	uint32_t	gpio34;
	uint32_t	gpio35;
	uint32_t	gpio36;
	uint32_t	gpio37;
	uint32_t	gpio38;
	uint32_t	gpio39;
	uint32_t	gpio40;
	uint32_t	gpio41;
	uint32_t	gpio42;
	uint32_t	gpio43;
	uint32_t	gpio44;
	uint32_t	gpio45;
	uint32_t	gpio46;
	uint32_t	gpio47;
	uint32_t	gpio48;
	uint32_t	gpio10;
	uint32_t	gpio49;
	uint32_t	gpio50;
	uint32_t	gpio51;
	uint32_t	gpio52;
	uint32_t	gpio53;
	uint32_t	gpio54;
	uint32_t	gpio55;
	uint32_t	gpio56;
	uint32_t	gpio57;
	uint32_t	gpio58;
	uint32_t	gpio59;
	uint32_t	gpio60;
	uint32_t	gpio61;
	uint32_t	gpio62;
	uint32_t	gpio6_2;
	uint32_t	gpio7_2;
	uint32_t	gpio8_2;
	uint32_t	gpio9_2;
	uint32_t	gpio10_2;
	uint32_t	gpio11_2;
	uint32_t	gpio12_2;
	uint32_t	gpio13_2;
	uint32_t	gpio63;
	uint32_t	gpio64;
	uint32_t	gpio65;
	uint32_t	gpio66;
	uint32_t	gpio67;
	uint32_t	gpio68;
	uint32_t	gpio69;
	uint32_t	gpio70;
	uint32_t	gpio71;
	uint32_t	gpio72;
	uint32_t	gpio73;
	uint32_t	gpio14_2;
	uint32_t	gpio15_2;
	uint32_t	gpio16_2;
	uint32_t	gpio17_2;
	uint32_t	gpio74;
	uint32_t	gpio75;
	uint32_t	gpio76;
	uint32_t	gpio77;
	uint32_t	gpio78;
	uint32_t	gpio79;
	uint32_t	gpio80;
	uint32_t	gpio81;
	uint32_t	gpio82;
	uint32_t	gpio83;
	uint32_t	gpio84;
	uint32_t	gpio85;
	uint32_t	gpio86;
	uint32_t	gpio87;
	uint32_t	gpio88;
	uint32_t	gpio89;
	uint32_t	gpio90;
	uint32_t	gpio91;
	uint32_t	gpio92;
	uint32_t	gpio93;
	uint32_t	gpio94;
	uint32_t	gpio95;
	uint32_t	gpio96;
	uint32_t	gpio97;
	uint32_t	gpio98;

	uint32_t	reserved4[43];

	uint32_t	gpio99;
	uint32_t	gpio100;
	uint32_t	gpio101;
	uint32_t	gpio102;
	uint32_t	gpio103;
	uint32_t	gpio104;
	uint32_t	gpio105;
	uint32_t	gpio106;
	uint32_t	gpio107;
	uint32_t	gpio108;
	uint32_t	gpio109;
	uint32_t	gpio110;
	uint32_t	gpio111;
	uint32_t	gpio112;
	uint32_t	gpio113;
	uint32_t	gpio114;
	uint32_t	gpio115;
	uint32_t	gpio116;
	uint32_t	gpio117;
	uint32_t	gpio118;
	uint32_t	gpio119;
	uint32_t	gpio120;
	uint32_t	gpio121;
	uint32_t	gpio122;
	uint32_t	gpio123;
	uint32_t	gpio124;
	uint32_t	gpio125;
	uint32_t	gpio126;
	uint32_t	gpio127;
	uint32_t	gpio0_2;
	uint32_t	gpio1_2;
	uint32_t	gpio2_2;
	uint32_t	gpio3_2;
	uint32_t	gpio4_2;
	uint32_t	gpio5_2;
};

#define MFPR_PULL_SEL		(1 << 15)
#define MFPR_PULLUP_EN		(1 << 14)
#define MFPR_PULLDOWN_EN	(1 << 13)
#define MFPR_DRIVE_OFFSET	10
#define MFPR_DRIVE_MASK		(0x7 << 10)
#define MFPR_DRIVE_FAST_1MA	(0x0 << 10)
#define MFPR_DRIVE_FAST_2MA	(0x1 << 10)
#define MFPR_DRIVE_FAST_3MA	(0x2 << 10)
#define MFPR_DRIVE_FAST_4MA	(0x3 << 10)
#define MFPR_DRIVE_SLOW_6MA	(0x4 << 10)
#define MFPR_DRIVE_FAST_6MA	(0x5 << 10)
#define MFPR_DRIVE_SLOW_10MA	(0x6 << 10)
#define MFPR_DRIVE_FAST_10MA	(0x7 << 10)
#define MFPR_SLEEP_SEL		(1 << 9)
#define MFPR_SLEEP_DATA		(1 << 8)
#define MFPR_SLEEP_OE_N		(1 << 7)
#define MFPR_EDGE_CLEAR		(1 << 6)
#define MFPR_EDGE_FALL_EN	(1 << 5)
#define MFPR_EDGE_RISE_EN	(1 << 4)
#define MFPR_AF_SEL_OFFSET	0
#define MFPR_AF_SEL_MASK	0x7

struct pxa_gpio_regs {
	uint32_t	gplr0;
	uint32_t	gplr1;
	uint32_t	gplr2;
	uint32_t	gpdr0;
	uint32_t	gpdr1;
	uint32_t	gpdr2;
	uint32_t	gpsr0;
	uint32_t	gpsr1;
	uint32_t	gpsr2;
	uint32_t	gpcr0;
	uint32_t	gpcr1;
	uint32_t	gpcr2;
	uint32_t	grer0;
	uint32_t	grer1;
	uint32_t	grer2;
	uint32_t	gfer0;
	uint32_t	gfer1;
	uint32_t	gfer2;
	uint32_t	gedr0;
	uint32_t	gedr1;
	uint32_t	gedr2;
	uint32_t	gafr0_l;
	uint32_t	gafr0_u;
	uint32_t	gafr1_l;
	uint32_t	gafr1_u;
	uint32_t	gafr2_l;
	uint32_t	gafr2_u;

#if defined(CONFIG_CPU_PXA27X) || defined(CONFIG_CPU_PXA3XX)
	uint32_t	gafr3_l;
	uint32_t	gafr3_u;
	uint32_t	reserved1[35];
	uint32_t	gplr3;
	uint32_t	reserved2[2];
	uint32_t	gpdr3;
	uint32_t	reserved3[2];
	uint32_t	gpsr3;
	uint32_t	reserved4[2];
	uint32_t	gpcr3;
	uint32_t	reserved5[2];
	uint32_t	grer3;
	uint32_t	reserved6[2];
	uint32_t	gfer3;
	uint32_t	reserved7[2];
	uint32_t	gedr3;
#endif

#if defined(CONFIG_CPU_PXA3XX)
	uint32_t	reserved8[173];
	uint32_t	gsdr0;
	uint32_t	gsdr1;
	uint32_t	gsdr2;
	uint32_t	gsdr3;
	uint32_t	reserved9[4];
	uint32_t	gcdr0;
	uint32_t	gcdr1;
	uint32_t	gcdr2;
	uint32_t	gcdr3;
	uint32_t	reserved10[4];
	uint32_t	gsrer0;
	uint32_t	gsrer1;
	uint32_t	gsrer2;
	uint32_t	gsrer3;
	uint32_t	reserved11[4];
	uint32_t	gcrer0;
	uint32_t	gcrer1;
	uint32_t	gcrer2;
	uint32_t	gcrer3;
	uint32_t	reserved12[4];
	uint32_t	gsfer0;
	uint32_t	gsfer1;
	uint32_t	gsfer2;
	uint32_t	gsfer3;
	uint32_t	reserved13[4];
	uint32_t	gcfer0;
	uint32_t	gcfer1;
	uint32_t	gcfer2;
	uint32_t	gcfer3;
#endif
};

#endif	/* __REGS_GPIO_H__ */
