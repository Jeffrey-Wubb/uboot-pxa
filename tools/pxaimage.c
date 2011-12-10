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

#define _GNU_SOURCE

#include "mkimage.h"
#include <image.h>
#include "pxaimage.h"

#define PXA_FILE_HDR_SIZE	0x1000

static uint8_t pxaimage_header[PXA_FILE_HDR_SIZE];
static uint32_t pxaimage_offset;

static int pxaimage_check_image_types(uint8_t type)
{
	if (type == IH_TYPE_PXAIMAGE)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}

static int pxaimage_verify_header(unsigned char *ptr, int image_size,
			struct mkimage_params *params)
{
/*
	struct ch_toc *toc = (struct ch_toc *)ptr;
	struct gp_header *gph = (struct gp_header *)(ptr+OMAP_CH_HDR_SIZE);
	uint32_t offset, size;

	while (toc->section_offset != 0xffffffff
			&& toc->section_size != 0xffffffff) {
		offset = toc->section_offset;
		size = toc->section_size;
		if (!offset || !size)
			return -1;
		if (offset >= OMAP_CH_HDR_SIZE ||
		    offset+size >= OMAP_CH_HDR_SIZE)
			return -1;
		toc++;
	}
	if (!valid_gph_size(gph->size))
		return -1;
	if (!valid_gph_load_addr(gph->load_addr))
		return -1;
*/
	return 0;
}

static void pxaimage_print_header(const void *ptr)
{
/*
	const struct ch_toc *toc = (struct ch_toc *)ptr;
	const struct gp_header *gph =
			(struct gp_header *)(ptr+OMAP_CH_HDR_SIZE);
	uint32_t offset, size;

	while (toc->section_offset != 0xffffffff
			&& toc->section_size != 0xffffffff) {
		offset = toc->section_offset;
		size = toc->section_size;

		if (offset >= OMAP_CH_HDR_SIZE ||
		    offset+size >= OMAP_CH_HDR_SIZE)
			exit(EXIT_FAILURE);

		printf("Section %s offset %x length %x\n",
			toc->section_name,
			toc->section_offset,
			toc->section_size);

		omapimage_print_section((struct ch_settings *)(ptr+offset));
		toc++;
	}

	if (!valid_gph_size(gph->size)) {
		fprintf(stderr,
			"Error: invalid image size %x\n",
			gph->size);
		exit(EXIT_FAILURE);
	}

	if (!valid_gph_load_addr(gph->load_addr)) {
		fprintf(stderr,
			"Error: invalid image load address %x\n",
			gph->size);
		exit(EXIT_FAILURE);
	}

	printf("GP Header: Size %x LoadAddr %x\n",
		gph->size, gph->load_addr);*/
}

static void pxaimage_enter_section(enum pxa_boot_section_types *state,
					char *line, int lineno)
{
	uint32_t idx;
	char *token, *saveptr;

	/* We're already parsing a section. */
	if (*state != PXA_BS_UNKN)
		return;

	token = strtok_r(line, " \t", &saveptr);
	if (!token)
		return;

	/* This isn't our line. */
	if (token[0] != '[')
		return;

	token = strtok_r(NULL, " \t", &saveptr);
	if (token == NULL) {
		fprintf(stderr, "Error: Missing section type (line %i)\n",
				lineno);
		exit(EXIT_FAILURE);
	}

	for (idx = 0; idx < ARRAY_SIZE(pxa_boot_sections); idx++)
		if (!strcmp(pxa_boot_sections[idx].type, token))
			break;

	if (idx == ARRAY_SIZE(pxa_boot_sections)) {
		fprintf(stderr, "Error: Unknown section type \"%s\" "
				"(line %i)\n", token, lineno);
		exit(EXIT_FAILURE);
	}

	*state = pxa_boot_sections[idx].result;
}

static void pxaimage_parse_ntim_header(enum pxa_boot_section_types *state,
					char *line, int lineno, char **ptr,
					char **link)
{
	time_t now;
	struct tm *tm;
	uint32_t idx, val;
	char *token, *saveptr, *trash;
	struct pxa_ntim_header *ntim_header = (struct pxa_ntim_header *)*ptr;

	token = strtok_r(line, " \t", &saveptr);
	if (!token)
		return;

	for (idx = 0; idx < ARRAY_SIZE(pxa_boot_sections); idx++)
		if (pxa_boot_sections[idx].result == PXA_BS_NTIM)
			break;

	/* Get current date for the image issue date. */
	time(&now);
	tm = gmtime(&now);
	tm->tm_year += 1900;
	tm->tm_mon++;

	/* Fill in the header from currently available information. */
	ntim_header->version	= 0x00030102;

	ntim_header->trusted	= 0;
	ntim_header->issue_date	=
		(tm->tm_year % 10) |
		(((tm->tm_year / 10) % 10) << 4) |
		(((tm->tm_year / 100) % 10) << 8) |
		((tm->tm_year / 1000) << 12) |
		((tm->tm_mon % 10) << 16) | ((tm->tm_mon / 10) << 20) |
		((tm->tm_mday % 10) << 24) | ((tm->tm_mday / 10) << 28);
	ntim_header->oem_unique_id = 0x55424f54;	/* UBOT */

	/* Figure out the boot mode. */
	for (idx = 0; idx < ARRAY_SIZE(pxa_boot_types); idx++)
		if (!strcmp(pxa_boot_types[idx].type, token))
			break;

	if (pxa_boot_types[idx].type == 0) {
		fprintf(stderr, "Error: Unknown boot flash type \"%s\" "
				"(line %i)\n", token, lineno);
		exit(EXIT_FAILURE);
	}

	token = strtok_r(NULL, " \t", &saveptr);
	if (token == NULL) {
		fprintf(stderr, "Error: Missing flash width "
			"(line %i)\n", lineno);
		exit(EXIT_FAILURE);
	}

	val = strtol(token, &trash, 10);
	if ((val != 8) && (val != 16)) {
		fprintf(stderr, "Error: Invalid flash width %i "
			"(line %i)\n", val, lineno);
		exit(EXIT_FAILURE);
	}

	if (!strcmp(pxa_boot_types[idx].type, "NAND") &&
		(pxa_boot_types[idx].width == 8) && (val == 16))
		idx++;

	ntim_header->boot_flash_sign = pxa_boot_types[idx].result;

	*state = PXA_BS_UNKN;

	*link = *ptr;
	*ptr += sizeof(struct pxa_ntim_header);
}

struct prog_ctx {
	uint8_t	src;
	uint8_t	dst;
	uint8_t	size;
};

static void pxaimage_parse_prog_header(enum pxa_boot_section_types *state,
					char *line, int lineno, char **ptr,
					char **link, int *images,
					struct prog_ctx *ctx)
{
	uint32_t idx, val;
	char *token, *arg, *saveptr, *trash;
	struct pxa_prog_header *prog_header = (struct pxa_prog_header *)*ptr;
	struct pxa_prog_header *prev_header = (struct pxa_prog_header *)*link;

	token = strtok_r(line, " \t", &saveptr);
	if (!token)
		return;

	/* New program section loaded, set it up. */
	if (!prog_header->image_id) {
		for (idx = 0; idx < ARRAY_SIZE(pxa_boot_sections); idx++)
			if (pxa_boot_sections[idx].result == *state)
				break;

		/* Fill in the header from currently available information. */
		prog_header->image_id	= pxa_boot_sections[idx].result;
		prev_header->next_image_id = prog_header->image_id;
	}

	/* Figure out the option and parameter. */
	arg = strtok_r(NULL, " \t", &saveptr);
	if (!arg) {
		fprintf(stderr, "Error: Missing argument for option \"%s\" "
				"(line %i)\n", token, lineno);
		exit(EXIT_FAILURE);
	}

	val = strtol(arg, &trash, 16);

	if (!strcmp(token, "SRC")) {
		ctx->src = 1;
		prog_header->flash_entry_addr = val;
	} else if (!strcmp(token, "DST")) {
		ctx->dst = 1;
		prog_header->load_addr = val;
	} else if (!strcmp(token, "SIZE")) {
		ctx->size = 1;
		prog_header->image_size = val;
	}

	/*
	 * Only after the section is complete, restart the parser for new
	 * sections to be read.
	 */
	if (ctx->src && ctx->dst && ctx->size) {
		*state = PXA_BS_UNKN;

		*link = *ptr;
		*ptr += sizeof(struct pxa_prog_header);

		*images += 1;
	}
}

static void pxaimage_parse_term_header(enum pxa_boot_section_types *state,
					char *line, int lineno, char *link,
					char *ntptr, int images)
{
	uint32_t idx;
	char *token, *saveptr;
	struct pxa_prog_header *prev_header = (struct pxa_prog_header *)link;
	struct pxa_ntim_header *ntim_header = (struct pxa_ntim_header *)ntptr;

	token = strtok_r(line, " \t", &saveptr);
	if (!token)
		return;

	/* Just fill the TERM header information and exit. */
	for (idx = 0; idx < ARRAY_SIZE(pxa_boot_sections); idx++)
		if (pxa_boot_sections[idx].result == *state)
			break;

	/* Fill in the header from currently available information. */
	prev_header->next_image_id = pxa_boot_sections[idx].result;
	ntim_header->num_images = images;

	*state = PXA_BS_UNKN;
}

struct opth_ctx {
	uint32_t	num_packages;
	uint32_t	size;
};

static void pxaimage_parse_opth_header(enum pxa_boot_section_types *state,
					char *line, int lineno, char **ptr,
					char **link, struct opth_ctx *ctx)
{
	uint32_t idx;
	char *token, *saveptr;
	struct pxa_package_header *header =
		(struct pxa_package_header *)*ptr;

	token = strtok_r(line, " \t", &saveptr);
	if (!token)
		return;

	/* Just fill the TERM header information and exit. */
	for (idx = 0; idx < ARRAY_SIZE(pxa_boot_sections); idx++)
		if (pxa_boot_sections[idx].result == *state)
			break;

	/* Fill in the header from currently available information. */
	header->wtptp_reserved_area_id = pxa_boot_sections[idx].result;

	/* Link ptr now always points to OPTH header */
	*link = *ptr;
	*ptr += sizeof(struct pxa_package_header);

	*state = PXA_BS_UNKN;

	ctx->size += sizeof(struct pxa_package_header);
}

static void pxaimage_parse_optt_header(enum pxa_boot_section_types *state,
					char *line, int lineno, char **ptr,
					char *link, char *ntptr,
					struct opth_ctx *ctx)
{
	uint32_t idx;
	char *token, *saveptr;
	struct pxa_package_header *header =
		(struct pxa_package_header *)link;
	struct pxa_ntim_header *ntim_header = (struct pxa_ntim_header *)ntptr;
	struct pxa_package_wrah *wrah = (struct pxa_package_wrah *)*ptr;

	token = strtok_r(line, " \t", &saveptr);
	if (!token)
		return;

	for (idx = 0; idx < ARRAY_SIZE(pxa_boot_sections); idx++)
		if (pxa_boot_sections[idx].result == *state)
			break;

	wrah->identifier = pxa_boot_sections[idx].result;
	wrah->size = sizeof(struct pxa_package_wrah);

	ctx->num_packages++;
	ctx->size += wrah->size;

	/* Fill in the header from currently available information. */
	header->num_reserved_packages = ctx->num_packages;
	ntim_header->size_of_reserved = ctx->size;
	*state = PXA_BS_UNKN;
}

struct ddrh_ctx {
	uint8_t	accr;
	uint8_t	mdcnfg;
	uint8_t	hcal;
	uint8_t	mdrefr;
};

static void pxaimage_parse_ddrh_header(enum pxa_boot_section_types *state,
					char *line, int lineno, char **ptr,
					struct opth_ctx *ctx,
					struct ddrh_ctx *ddrh_ctx)
{
	uint32_t idx, val;
	char *token, *arg, *saveptr, *trash;
	struct pxa_package_ddrh *ddrh_header = (struct pxa_package_ddrh *)*ptr;

	token = strtok_r(line, " \t", &saveptr);
	if (!token)
		return;

	/* New DDrH section loaded, set it up. */
	if (!ddrh_header->wrah.identifier) {
		for (idx = 0; idx < ARRAY_SIZE(pxa_boot_sections); idx++)
			if (pxa_boot_sections[idx].result == *state)
				break;

		/* Fill in the header from currently available information. */
		ddrh_header->wrah.identifier = pxa_boot_sections[idx].result;
		ddrh_header->wrah.size = sizeof(struct pxa_package_ddrh);
	}

	/* Figure out the option and parameter. */
	arg = strtok_r(NULL, " \t", &saveptr);
	if (!arg) {
		fprintf(stderr, "Error: Missing argument for option \"%s\" "
				"(line %i)\n", token, lineno);
		exit(EXIT_FAILURE);
	}

	val = strtol(arg, &trash, 16);

	if (!strcmp(token, "ACCR")) {
		ddrh_ctx->accr = 1;
		ddrh_header->accr = val;
	} else if (!strcmp(token, "MDCNFG")) {
		ddrh_ctx->mdcnfg = 1;
		ddrh_header->mdcnfg = val;
	} else if (!strcmp(token, "HCAL")) {
		ddrh_ctx->hcal = 1;
		ddrh_header->hcal = val;
	} else if (!strcmp(token, "MDREFR")) {
		ddrh_ctx->mdrefr = 1;
		ddrh_header->mdrefr = val;
	}

	/*
	 * Only after the section is complete, restart the parser for new
	 * sections to be read.
	 */
	if (ddrh_ctx->accr && ddrh_ctx->mdcnfg &&
		ddrh_ctx->hcal && ddrh_ctx->mdrefr) {
		*state = PXA_BS_UNKN;

		*ptr += sizeof(struct pxa_package_ddrh);

		ctx->num_packages++;
		ctx->size += sizeof(struct pxa_package_ddrh);
	}
}

struct gpio_ctx {
	struct pxa_package_gpio	*gpio_header;
	uint8_t			counted;
};

static void pxaimage_parse_gpio_header(enum pxa_boot_section_types *state,
					char *line, int lineno, char **ptr,
					struct opth_ctx *ctx,
					struct gpio_ctx *gpio_ctx)
{
	uint32_t idx, addr, value;
	char *token, *arg, *saveptr, *trash;
	struct pxa_package_gpio *gpio_header = (struct pxa_package_gpio *)*ptr;
	struct pxa_package_gpio_pair *pair;

	token = strtok_r(line, " \t", &saveptr);
	if (!token)
		return;

	/* New GPIO section loaded, set it up. */
	if (!gpio_ctx->counted) {
		for (idx = 0; idx < ARRAY_SIZE(pxa_boot_sections); idx++)
			if (pxa_boot_sections[idx].result == *state)
				break;

		/* Fill in the header from currently available information. */
		gpio_header->wrah.identifier = pxa_boot_sections[idx].result;
		gpio_header->wrah.size = sizeof(struct pxa_package_gpio);

		gpio_ctx->gpio_header = gpio_header;
	}

	if (!strcmp(token, "ENDG")) {
		*state = PXA_BS_UNKN;
		return;
	}

	addr = strtol(token, &trash, 16);

	/* Figure out the option and parameter. */
	arg = strtok_r(NULL, " \t", &saveptr);
	if (!arg) {
		fprintf(stderr, "Error: Missing value for address %08x "
				"(line %i)\n", addr, lineno);
		exit(EXIT_FAILURE);
	}

	value = strtol(arg, &trash, 16);

	if (!gpio_ctx->counted) {
		*ptr += sizeof(struct pxa_package_gpio);
		ctx->num_packages++;
		ctx->size += sizeof(struct pxa_package_gpio);
		gpio_ctx->counted = 1;
	}

	pair = (struct pxa_package_gpio_pair *)*ptr;
	pair->addr = addr;
	pair->value = value;
	*ptr += sizeof(struct pxa_package_gpio_pair);
	ctx->size += sizeof(struct pxa_package_gpio_pair);
	gpio_ctx->gpio_header->num_gpios++;
	gpio_ctx->gpio_header->wrah.size +=
		sizeof(struct pxa_package_gpio_pair);
}

static void pxaimage_set_header(void *ptr_v, struct stat *sbuf, int ifd,
				struct mkimage_params *params)
{
	FILE *fd = NULL;
	char *line = NULL;
	int lineno = 0;
	size_t len;

	char *token, *saveptr;
	char *ntim_ptr = (char *)ptr_v;
	char *ptr = ntim_ptr;
	char *link = ptr;

	struct opth_ctx opth_ctx = { 0, 0 };
	int images = 0;

	struct prog_ctx prog_ctx;
	struct ddrh_ctx ddrh_ctx;
	struct gpio_ctx gpio_ctx;

	enum pxa_boot_section_types state = PXA_BS_UNKN;

	fd = fopen(params->imagename, "r");
	if (fd == 0) {
		fprintf(stderr, "Error: %s - Can't open config file\n",
				params->imagename);
		exit(EXIT_FAILURE);
	}

	memset(ptr, 0, PXA_FILE_HDR_SIZE);

	/*
	 * Very simple parsing, line starting with # are comments
	 * and are dropped
	 */
	while (getline(&line, &len, fd) != -1) {
		lineno++;

	printf("PARSE %08x @ [%04i] \"%s\"\n", state, lineno, line);

		token = strtok_r(line, "\r\n", &saveptr);

		/* Ignore white lines. */
		if (token == NULL)
			continue;

		/* Ignore comments -- lines starting with '#'. */
		if (token[0] == '#')
			continue;

		switch (state) {
		case PXA_BS_UNKN:
			pxaimage_enter_section(&state, line, lineno);

			/* Clear contexts */
			memset(&prog_ctx, 0, sizeof(struct prog_ctx));
			memset(&ddrh_ctx, 0, sizeof(struct ddrh_ctx));
			memset(&gpio_ctx, 0, sizeof(struct gpio_ctx));

			/* Parameter-less subsection anchors */
			if (state == PXA_BS_TERM)
				pxaimage_parse_term_header(&state, line, lineno,
							link, ntim_ptr, images);
			if (state == PXA_BS_OPTH)
				pxaimage_parse_opth_header(&state, line, lineno,
							&ptr, &link, &opth_ctx);
			if (state == PXA_BS_OPTT)
				pxaimage_parse_optt_header(&state, line, lineno,
							&ptr, link, ntim_ptr,
							&opth_ctx);
			break;
		case PXA_BS_NTIM:
			pxaimage_parse_ntim_header(&state, line, lineno,
							&ptr, &link);
			break;
		case PXA_BS_TIMH:
		case PXA_BS_OBMI:
		case PXA_BS_OSLO:
			pxaimage_parse_prog_header(&state, line, lineno,
							&ptr, &link, &images,
							&prog_ctx);
			break;
		case PXA_BS_DDRH:
			pxaimage_parse_ddrh_header(&state, line, lineno,
							&ptr, &opth_ctx,
							&ddrh_ctx);
			break;
		case PXA_BS_GPIO:
			pxaimage_parse_gpio_header(&state, line, lineno,
							&ptr, &opth_ctx,
							&gpio_ctx);
			break;
		default:
			fprintf(stderr, "Error: Unknown syntax error "
					"(line %i)\n", lineno);
			exit(EXIT_FAILURE);
		}
	}

	if (line)
		free(line);

	fclose(fd);

	return;
}

int pxaimage_check_params(struct mkimage_params *params)
{
	if (!params)
		return -1;

	if (!strlen(params->imagename)) {
		fprintf(stderr, "Error: %s - Configuration file not specified, "
			"it is needed for imximage generation\n",
			params->cmdname);
		return -1;
	}

	return	(params->dflag && (params->fflag || params->lflag)) ||
		(params->fflag && (params->dflag || params->lflag)) ||
		(params->lflag && (params->dflag || params->fflag)) ||
		(params->xflag) || !(strlen(params->imagename));
}

/*
 * pxaimage parameters
 */
static struct image_type_params pxaimage_params = {
	.name		= "Marvell PXA3xx/V3.xx Boot Image support",
	.header_size	= PXA_FILE_HDR_SIZE,
	.hdr		= (void *)&pxaimage_header,
	.check_image_type = pxaimage_check_image_types,
	.verify_header	= pxaimage_verify_header,
	.print_header	= pxaimage_print_header,
	.set_header	= pxaimage_set_header,
	.check_params	= pxaimage_check_params,
};

void init_pxa_image_type(void)
{
	pxaimage_offset = 0;
	mkimage_register(&pxaimage_params);
}
