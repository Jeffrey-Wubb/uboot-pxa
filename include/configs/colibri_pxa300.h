/*
 * Toradex Colibri PXA300/PXA310 configuration file
 *
 * Copyright (C) 2009-2011 Marek Vasut <marek.vasut@gmail.com>
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

#ifndef	__CONFIG_H
#define	__CONFIG_H

/*
 * High Level Board Configuration Options
 */
#define	CONFIG_CPU_PXA3XX	1	/* Marvell Monahans CPU */
#define	CONFIG_CPU_PXA310	1	/* Marvell Monahans L/LV CPU */
#define	CONFIG_COLIBRI_PXA300	1	/* Colibri PXA320 board */
#define	CONFIG_SYS_TEXT_BASE		0xa0001000

#define	CONFIG_DISPLAY_CPUINFO

#define	CONFIG_PXA_GPIO

/*
 * Environment settings
 */
#define	CONFIG_ENV_OVERWRITE
#define	CONFIG_SYS_MALLOC_LEN		(1024 * 1024)
#define	CONFIG_ARCH_CPU_INIT
#define	CONFIG_BOOTCOMMAND						\
	"if mmc init && fatload mmc 0 0xa0000000 uImage; then "		\
		"bootm 0xa0000000; "					\
	"fi; "								\
	"if usb reset && fatload usb 0 0xa0000000 uImage; then "	\
		"bootm 0xa0000000; "					\
	"fi; "								\
	"bootm 0x80000;"
#define	CONFIG_BOOTARGS			"console=tty0 console=ttyS0,115200"
#define	CONFIG_TIMESTAMP
#define	CONFIG_BOOTDELAY		5	/* Autoboot delay */
#define	CONFIG_CMDLINE_TAG
#define	CONFIG_SETUP_MEMORY_TAGS
#define	CONFIG_LZMA			/* LZMA compression support */
#define	CONFIG_OF_LIBFDT

#define	CONFIG_EXTRA_ENV_SETTINGS	\
	"update=nand erase 0x0 0xa0000 ; nand write 0xa0000000 0x0 0xa0000\0"

/*
 * Serial Console Configuration
 */
#define	CONFIG_PXA_SERIAL
#define	CONFIG_FFUART			1
#define	CONFIG_BAUDRATE			115200
#define	CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

/*
 * Bootloader Components Configuration
 */
#include <config_cmd_default.h>

#define	CONFIG_CMD_ENV
#define	CONFIG_CMD_MMC
#define	CONFIG_CMD_NAND
#undef	CONFIG_CMD_UBI
#define	CONFIG_CMD_USB
#undef	CONFIG_CMD_FLASH
#undef	CONFIG_CMD_IMLS
#define	CONFIG_CMD_NET
#undef	CONFIG_CMD_NFS

/*
 * Networking Configuration
 * AX88696L / NE2000 chip on the Colibri PXA320 board
 */
#ifdef	CONFIG_CMD_NET
#define	CONFIG_CMD_PING
#define	CONFIG_CMD_DHCP

#define	CONFIG_DRIVER_AX88796L
#define	CONFIG_DRIVER_NE2000_BASE       0x10000000
#define	CONFIG_NE2000_NOPROM
#endif

/*
 * HUSH Shell Configuration
 */
#define	CONFIG_SYS_LONGHELP
#define	CONFIG_SYS_PROMPT	"=> "
#define	CONFIG_SYS_CBSIZE	1024		/* Console I/O buffer size */
#define	CONFIG_SYS_PBSIZE	\
	(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
						/* Print buffer size */
#define	CONFIG_SYS_MAXARGS	32		/* Max number of command args */
#define	CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE
						/* Boot argument buffer size */
#define	CONFIG_VERSION_VARIABLE			/* U-BOOT version */
#define	CONFIG_AUTO_COMPLETE			/* Command auto complete */
#define	CONFIG_CMDLINE_EDITING			/* Command history etc */
#define	CONFIG_SYS_HUSH_PARSER
#define	CONFIG_SYS_PROMPT_HUSH_PS2	"> "

/*
 * Clock Configuration
 */
#define	CONFIG_SYS_HZ			1000		/* Timer @ 3250000 Hz */

/*
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */
#define	CONFIG_STACKSIZE		(128 * 1024)	/* regular stack */
#ifdef	CONFIG_USE_IRQ
#define	CONFIG_STACKSIZE_IRQ		(4 * 1024)	/* IRQ stack */
#define	CONFIG_STACKSIZE_FIQ		(4 * 1024)	/* FIQ stack */
#endif

/*
 * DRAM Map
 */
#define	CONFIG_NR_DRAM_BANKS		1		/* We have 1 bank of DRAM */
#define	PHYS_SDRAM_1			0xa0000000	/* SDRAM Bank #1 */
#define	PHYS_SDRAM_1_SIZE		0x04000000	/* 128 MB */

#define	CONFIG_SYS_DRAM_BASE		0xa0000000	/* CS0 */
#define	CONFIG_SYS_DRAM_SIZE		0x04000000	/* 128 MB DRAM */

#define	CONFIG_SYS_MEMTEST_START	0xa0400000	/* memtest works on */
#define	CONFIG_SYS_MEMTEST_END		0xa0800000	/* 4 ... 8 MB in DRAM */

#define	CONFIG_SYS_LOAD_ADDR		PHYS_SDRAM_1
#define	CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM_1
#define	CONFIG_SYS_INIT_SP_ADDR		0x5c018000

#define	CONFIG_SYS_PXA3XX_DDR_MDCNFG	0x329
#define	CONFIG_SYS_PXA3XX_DDR_RCRNG	0x2
#define	CONFIG_SYS_PXA3XX_DDR_REI	0x50
#define	CONFIG_SYS_PXA3XX_DDR_MDMRS	0x33

/*
 * NAND
 */
#ifdef	CONFIG_CMD_NAND
#define	CONFIG_NAND_PXA3XX
#define	CONFIG_NAND_PXA3XX_KEEP_CONFIG
#define	CONFIG_SYS_NAND_BASE		0x43100000
#define	CONFIG_SYS_MAX_NAND_DEVICE	1	/* Max number of NAND devices */

/* Environment is in NAND */
#define	CONFIG_ENV_IS_IN_NAND
#define	CONFIG_ENV_SIZE			(16 * 1024)
#define	CONFIG_ENV_SIZE_REDUND		CONFIG_ENV_SIZE
#define	CONFIG_ENV_SECT_SIZE		(128 * 1024)
#define	CONFIG_ENV_RANGE		(512 * 1024)
#define	CONFIG_ENV_OFFSET		0x100000
#define	CONFIG_ENV_OFFSET_REDUND	\
		(CONFIG_ENV_OFFSET + CONFIG_ENV_RANGE)

/* UBI support for NAND. Compiled only into main U-Boot. */
#ifndef	CONFIG_SPL_BUILD
#ifdef	CONFIG_CMD_UBI
#define	CONFIG_CMD_UBIFS
#define	CONFIG_CMD_MTDPARTS
#define	CONFIG_RBTREE
#define	CONFIG_LZO
#endif

/* MTD parts */
#define	CONFIG_MTD_DEVICE
#define	CONFIG_MTD_PARTITIONS
#define	MTDIDS_DEFAULT			"nand0=pxa3xx-nand.0"
#define	MTDPARTS_DEFAULT			\
	"mtdparts=pxa3xx-nand.0:"		\
		"1m(bootloader)ro,"		\
		"512k(environment),"		\
		"512k(redundant-environment),"	\
		"4m(kernel),"			\
		"-(filesystem)"
#endif

#else

#define	CONFIG_ENV_IS_NOWHERE		1

#endif

#define	CONFIG_SYS_NO_FLASH

#include "pxa-common.h"

#endif	/* __CONFIG_H */
