/*
 * Control GPIO pins on the fly
 *
 * Copyright (c) 2008-2011 Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
 */

#include <common.h>
#include <command.h>
#include <errno.h>
#include <dm.h>
#include <asm/gpio.h>
#include<linux/delay.h>


static int do_blink(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int value = 0, ret;
	unsigned int gpio;
	const char *str_cmd, *str_gpio = NULL;

	if (argc > 0)
	{
		str_gpio = argv[1];
		str_cmd = argv[0];
	}

	//strncmp(str_cmd, "status", 2);
	
	ret = gpio_lookup_name(str_gpio, NULL, NULL, &gpio);
	if (ret) {
		printf("GPIO: '%s' not found\n", str_gpio);
		return cmd_process_error(cmdtp, ret);
	}

	/* turn the gpio name into a gpio number */
	gpio = name_to_gpio(str_gpio);
	if (gpio < 0)
	{
		printf("gpio: requesting pin %u failed\n", gpio);
		return -1;
	}

	/* grab the pin before we tweak it */
	ret = gpio_request(gpio, "cmd_gpio");
	if (ret && ret != -EBUSY) {
		printf("gpio: requesting pin %u failed\n", gpio);
		return -1;
	}

	while(1)
	{
		value =!value;
		gpio_direction_output(gpio, value);
		mdelay(100);
		if(ctrlc())
			return value;
	}
	
	return value;
}

U_BOOT_CMD(blink, 4, 0, do_blink,
	   "query and control gpio pins",
	   "<input|set|clear|toggle> <pin>\n"
	   "    - input/set/clear/toggle the specified pin\n"
	   "gpio status [-a] [<bank> | <pin>]  - show [all/claimed] GPIOs");
