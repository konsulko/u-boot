/*
 * (C) Copyright 2011, 2012, 2013
 * Yuri Tikhonov, Emcraft Systems, yur@emcraft.com
 * Alexander Potashev, Emcraft Systems, aspotashev@emcraft.com
 * Vladimir Khusainov, Emcraft Systems, vlad@emcraft.com
 * Pavel Boldin, Emcraft Systems, paboldin@emcraft.com
 *
 * (C) Copyright 2015
 * Kamil Lulko, <rev13@wp.pl>
 *
 * Copyright 2015 ATS Advanced Telematics Systems GmbH
 * Copyright 2015 Konsulko Group, Matt Porter <mporter@konsulko.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/io.h>
#include <asm/armv7m.h>
#include <asm/arch/stm32.h>
#include <asm/arch/gpio.h>

DECLARE_GLOBAL_DATA_PTR;

const struct stm32_gpio_ctl gpio_ctl_usart[] = {
	/* TX */
	{
		.mode = STM32_GPIO_MODE_OUT_50M,
		.ocnf = STM32_GPIO_OCNF_AF_PP,
	},
	/* RX */
	{
		.mode = STM32_GPIO_MODE_IN,
		.icnf = STM32_GPIO_ICNF_IN_FLT,
	}
};

static const struct stm32_gpio_dsc usart1_gpio[] = {
	{STM32_GPIO_PORT_A, STM32_GPIO_PIN_9},	/* TX */
	{STM32_GPIO_PORT_A, STM32_GPIO_PIN_10},	/* RX */
};

int uart2_setup_gpio(void)
{
	int i;
	int rv = 0;

	for (i = 0; i < ARRAY_SIZE(usart1_gpio); i++) {
		rv = stm32_gpio_config(&usart1_gpio[i], &gpio_ctl_usart[i]);
		if (rv)
			goto out;
	}

out:
	return rv;
}

int dram_init(void)
{
	gd->ram_size = CONFIG_SYS_RAM_SIZE;

	return 0;
}

u32 get_board_rev(void)
{
	return 0;
}

int board_early_init_f(void)
{
	int res;

	res = uart2_setup_gpio();
	if (res)
		return res;

	return 0;
}

int board_init(void)
{
	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;

	return 0;
}
