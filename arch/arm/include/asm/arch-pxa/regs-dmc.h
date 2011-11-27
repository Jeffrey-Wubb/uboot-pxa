/*
 * PXA3xx Dynamic Memory Controller register definitions
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

#ifndef	__REGS_DMC_H__
#define	__REGS_DMC_H__

#define	DMC_BASE	0x48100000

struct pxa3xx_dmc_regs {
	uint32_t	mdcnfg;
	uint32_t	mdrefr;
	uint32_t	reserved1[14];
	uint32_t	mdmrs;
	uint32_t	reserved2[7];
	uint32_t	ddr_hcal;
	uint32_t	reserved3;
	uint32_t	ddr_wcal;
	uint32_t	reserved4;
	uint32_t	dmcier;
	uint32_t	reserved5;
	uint32_t	dmcisr;
	uint32_t	reserved6;
	uint32_t	ddr_dls;
	uint32_t	reserved7[3];
	uint32_t	empi;
	uint32_t	reserved8[27];
	uint32_t	rcomp;
	uint32_t	reserved9[3];
	uint32_t	pad_ma;
	uint32_t	pad_mdmsb;
	uint32_t	pad_mdlsb;
	uint32_t	pad_sdram;
	uint32_t	pad_sdclk;
	uint32_t	pad_sdcs;
};

#define	MDCNFG_DMCEN			(1 << 30)
#define	MDCNFG_HWFREQ			(1 << 29)
#define	MDCNFG_DTC_OFFSET		8
#define	MDCNFG_DTC_MASK			(0x3 << MDCNFG_DTC_OFFSET)
#define	MDCNFG_DRAC_OFFSET		5
#define	MDCNFG_DRAC_MASK		(0x3 << MDCNFG_DTC_OFFSET)
#define	MDCNFG_DCAC_OFFSET		3
#define	MDCNFG_DCAC_MASK		(0x3 << MDCNFG_DTC_OFFSET)
#define	MDCNFG_DBW			(1 << 2)
#define	MDCNFG_DCSE1			(1 << 1)
#define	MDCNFG_DCSE0			(1 << 0)

#define	MDREFR_SWREF			(1 << 8)
#define	MDREFR_DRI_OFFSET		0
#define	MDREFR_DRI_MASK			(0xff << MDREFR_DRI_OFFSET)

#define	MDMRS_MDCS1			(1 << 31)
#define	MDMRS_MDCS0			(1 << 30)
#define	MDMRS_MDCS0_OFFSET		30
#define	MDMRS_MDCOND			(1 << 29)
#define	MDMRS_MDPEND			(1 << 28)
#define	MDMRS_MDBA_OFFSET		15
#define	MDMRS_MDBA_MASK			(0x3 << MDMRS_MDBA_OFFSET)
#define	MDMRS_MDMRS_OFFSET		0
#define	MDMRS_MDMRS_MASK		(0x3fff << MDMRS_MDMRS_OFFSET)

#define	DDR_HCAL_HCEN			(1 << 31)
#define	DDR_HCAL_HCPROG			(1 << 28)
#define	DDR_HCAL_HCOFF1_OFFSET		10
#define	DDR_HCAL_HCOFF1_MASK		(0xf << DDR_HCAL_HCOFF1_OFFSET)
#define	DDR_HCAL_HCOFF0_OFFSET		6
#define	DDR_HCAL_HCOFF0_MASK		(0xf << DDR_HCAL_HCOFF0_OFFSET)
#define	DDR_HCAL_HCRNG_OFFSET		0
#define	DDR_HCAL_HCRNG_MASK		(0x1f << DDR_HCAL_HCRNG_OFFSET)

#define	DDR_WCAL_WCEN			(1 << 31)
#define	DDR_WCAL_WSDLV_STATUS_OFFSET	16
#define	DDR_WCAL_WSDLV_STATUS_MASK	(0x7f << DDR_WCAL_WCOFF_OFFSET)
#define	DDR_WCAL_WCOFF_OFFSET		8
#define	DDR_WCAL_WCOFF_MASK		(0xf << DDR_WCAL_WCOFF_OFFSET)

#define	DMCIER_ERCI			(1 << 31)
#define	DMCIER_EORF			(1 << 30)
#define	DMCIER_EDLP			(1 << 29)

#define	DMCISR_RCI			(1 << 31)
#define	DMCISR_ORF			(1 << 30)
#define	DMCISR_DLP			(1 << 29)
#define	DMCISR_PCODE_OFFSET		22
#define	DMCISR_PCODE_MASK		(0x7f << DMCISR_PCODE_OFFSET)
#define	DMCISR_NCODE_OFFSET		15
#define	DMCISR_NCODE_MASK		(0x7f << DMCISR_NCODE_OFFSET)
#define	DMCISR_PDV_OFFSET		8
#define	DMCISR_PDV_MASK			(0x7f << DMCISR_PDV_OFFSET)
#define	DMCISR_SLFREF			(1 << 7)
#define	DMCISR_ORV_OFFSET		0
#define	DMCISR_ORV_MASK			(0x7f << DMCISR_ORV_OFFSET)

#define	DDR_DLS_SSDLV3_OFFSET		24
#define	DDR_DLS_SSDLV3_MASK		(0x7f << DDR_DLS_SSDLV3_OFFSET)
#define	DDR_DLS_SSDLV2_OFFSET		16
#define	DDR_DLS_SSDLV2_MASK		(0x7f << DDR_DLS_SSDLV2_OFFSET)
#define	DDR_DLS_SSDLV1_OFFSET		8
#define	DDR_DLS_SSDLV1_MASK		(0x7f << DDR_DLS_SSDLV1_OFFSET)
#define	DDR_DLS_SSDLV0_OFFSET		0
#define	DDR_DLS_SSDLV0_MASK		(0x7f << DDR_DLS_SSDLV0_OFFSET)

#define	EMPI_PD_DQS			(1 << 31)
#define	EMPI_PW_DQN			(1 << 30)
#define	EMPI_SCHM_CMD			(1 << 29)
#define	EMPI_SCHM_DMEM_EN		(1 << 28)

#define	RCOMP_SWEVAL			(1 << 31)
#define	RCOMP_UPDATE			(1 << 30)
#define	RCOMP_RCRNG_OFFSET		25
#define	RCOMP_RCRNG_MASK		(0x1f << RCOMP_RCRNG_OFFSET)
#define	RCOMP_REI_OFFSET		0
#define	RCOMP_REI_MASK			(0xfffff << RCOMP_REI_OFFSET)

#endif	/* __REGS_DMC_H__ */
