/*
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __PXAIMAGE_H__
#define __PXAIMAGE_H__

enum pxa_boot_section_types {
	PXA_BS_NTIM = 0x4e54494d,
	PXA_BS_TIMH = 0x54494d48,
	PXA_BS_OBMI = 0x4f424d49,
	PXA_BS_OSLO = 0x4f534c4f,
	PXA_BS_OPTH = 0x4f505448,
	PXA_BS_GPIO = 0x4750494f,
	PXA_BS_DDRH = 0x44447248,
	PXA_BS_OPTT = 0x5465726d,
	PXA_BS_UNKN = 0xaa55aa55,	/* Fake state entry */
	PXA_BS_TERM = 0xffffffff,
};

struct pxa_boot_section {
	char		*type;
	uint32_t	result;
};

static const struct pxa_boot_section pxa_boot_sections[] = {
	{ "NTIM", PXA_BS_NTIM },
	{ "TIMH", PXA_BS_TIMH },
	{ "OBMI", PXA_BS_OBMI },
	{ "OSLO", PXA_BS_OSLO },
	{ "TERM", PXA_BS_TERM },
	{ "OPTH", PXA_BS_OPTH },
	{ "DDRH", PXA_BS_DDRH },
	{ "GPIO", PXA_BS_GPIO },
	{ "OPTT", PXA_BS_OPTT },
	{ "UNKN", PXA_BS_UNKN },
};

struct pxa_boot_type {
	char		*type;
	uint8_t		width;
	uint32_t	result;
};

static const struct pxa_boot_type pxa_boot_types[] = {
	{ "NAND",	8,	0x4e414e06 },
	{ "NAND",	16,	0x4e414e04 },
	{ "MDOC",	16,	0x4e414e01 },
	{ "ONENAND",	16,	0x4e414e02 },
	{ "NOR",	16,	0x58495005 },
	{ "NOR",	16,	0x58495007 },
	{ "UNKNOWN",	0,	0x00000000 },
};

struct pxa_ntim_header {
	uint32_t	version;
	uint32_t	identifier;
	uint32_t	trusted;
	uint32_t	issue_date;
	uint32_t	oem_unique_id;

	uint32_t	reserved1[5];
	uint32_t	boot_flash_sign;

	uint32_t	num_images;
	uint32_t	reserved2;
	uint32_t	size_of_reserved;
};

struct pxa_prog_header {
	uint32_t	image_id;
	uint32_t	next_image_id;
	uint32_t	flash_entry_addr;
	uint32_t	load_addr;
	uint32_t	image_size;
	uint32_t	reserved[10];
};

struct pxa_package_header {
	uint32_t	wtptp_reserved_area_id;
	uint32_t	num_reserved_packages;
};

struct pxa_package_wrah {
	uint32_t	identifier;
	uint32_t	size;
};

struct pxa_package_ddrh {
	struct pxa_package_wrah	wrah;
	uint32_t		accr;
	uint32_t		mdcnfg;
	uint32_t		hcal;
	uint32_t		mdrefr;
};

struct pxa_package_gpio {
	struct pxa_package_wrah	wrah;
	uint32_t		num_gpios;
};

struct pxa_package_gpio_pair {
	uint32_t	addr;
	uint32_t	value;
};

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#endif	/* __PXAIMAGE_H__ */
