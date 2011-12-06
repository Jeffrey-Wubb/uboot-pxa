/*
 * PXA GPIO driver
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
#include <asm/arch/regs-gpio.h>
#include <asm/errno.h>

int pxa_gpio_is_valid(int gp)
{
#ifdef CONFIG_CPU_PXA26X
	return ((gp >= 0) && (gp <= 89)
#endif
	if (cpu_is_pxa25x())
		return (gp >= 0) && (gp <= 84);
	if (cpu_is_pxa27x())
		/* GPIO 2, 5, 6, 7, 8 is reserved in PXA27x */
		return (gp >= 0) && (gp <= 120) && (gp != 2) &&
			!((gp >= 5) && (gp <= 8));
	if (cpu_is_pxa30x() || cpu_is_pxa31x() || cpu_is_pxa32x())
		return (gp >= 0) && (gp <= 127);

	return 0;
}

int gpio_get_value(int gp)
{
	struct pxa_gpio_regs *regs = (struct pxa_gpio_regs *)GPIO_BASE;
	uint32_t bank = gp >> 5;
	uint32_t gpio = gp & 0x1f;

	switch (bank) {
	case 0:
		return readl(&regs->gpsr0) & (1 << gpio);
	case 1:
		return readl(&regs->gpsr1) & (1 << gpio);
	case 2:
		return readl(&regs->gpsr2) & (1 << gpio);
	case 3:
		return readl(&regs->gpsr3) & (1 << gpio);
	default:
		return -EINVAL;
	}

}

int gpio_set_value(int gp, int value)
{
	struct pxa_gpio_regs *regs = (struct pxa_gpio_regs *)GPIO_BASE;
	uint32_t bank = gp >> 5;
	uint32_t gpio = gp & 0x1f;
	uint32_t val = value ? (1 << gpio) : 0;

	switch (bank) {
	case 0:
		clrsetbits_le32(&regs->gpsr0, 1 << gpio, val);
		return 0;
	case 1:
		clrsetbits_le32(&regs->gpsr1, 1 << gpio, val);
		return 0;
	case 2:
		clrsetbits_le32(&regs->gpsr2, 1 << gpio, val);
		return 0;
	case 3:
		clrsetbits_le32(&regs->gpsr3, 1 << gpio, val);
		return 0;
	}

	return -EINVAL;
}

int gpio_direction_input(int gp)
{
	struct pxa_gpio_regs *regs = (struct pxa_gpio_regs *)GPIO_BASE;
	uint32_t bank = gp >> 5;
	uint32_t gpio = gp & 0x1f;

	switch (bank) {
	case 0:
		setbits_le32(&regs->gpdr0, 1 << gpio);
		break;
	case 1:
		setbits_le32(&regs->gpdr1, 1 << gpio);
		break;
	case 2:
		setbits_le32(&regs->gpdr2, 1 << gpio);
		break;
	case 3:
		setbits_le32(&regs->gpdr3, 1 << gpio);
		break;
	default:
		return -EINVAL;
	}

#ifdef CONFIG_CPU_PXA26X
	/* GPIO 85-89 has inverted direction settings on PXA26x. */
	if ((bank == 2) && (gpio >= 85))
		clrbits_le32(&regs->gpdr2, 1 << gpio);
#endif

	return 0;
}

int gpio_direction_output(int gp, int value)
{
	struct pxa_gpio_regs *regs = (struct pxa_gpio_regs *)GPIO_BASE;
	uint32_t bank = gp >> 5;
	uint32_t gpio = gp & 0x1f;

	switch (bank) {
	case 0:
		setbits_le32(&regs->gpdr0, 1 << gpio);
		break;
	case 1:
		setbits_le32(&regs->gpdr1, 1 << gpio);
		break;
	case 2:
		setbits_le32(&regs->gpdr2, 1 << gpio);
		break;
	case 3:
		setbits_le32(&regs->gpdr3, 1 << gpio);
		break;
	default:
		return -EINVAL;
	}

#ifdef CONFIG_CPU_PXA26X
	/* GPIO 85-89 has inverted direction settings on PXA26x. */
	if ((bank == 2) && (gpio >= 85))
		clrbits_le32(&regs->gpdr2, 1 << gpio);
#endif

	return gpio_set_value(gp, value);
}

int gpio_request(int gp, const char *label)
{
	return pxa_gpio_is_valid(gp) ? 0 : -EINVAL;
}

void gpio_free(int gp)
{
}

void gpio_toggle_value(int gp)
{
	gpio_set_value(gp, !gpio_get_value(gp));
}
