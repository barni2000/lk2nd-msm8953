// SPDX-License-Identifier: BSD-3-Clause
/* Copyright (c) 2022, Stephan Gerhold <stephan@gerhold.net> */

#include <board.h>
#include <boot.h>
#include <clock.h>
#include <platform/iomap.h>
#include <reg.h>

#define MHZ				1000000

static bool platform_has_second_cluster(void)
{
	switch (board_platform_id()) {
		case MSM8953:
		case SDM632:
		case SDA632:
			return true;
		default:
			/* MSM8916/MSM8936 have only one CPU cluster */
			return false;
	};
}

static int lk2nd_8953_clock_setup(void *dtb, const char *cmdline,
				  enum boot_type boot_type)
{

	if (!platform_has_second_cluster())
		return 0;

	// select clock for secondary cluster
	clk_get_set_enable("a53ssmux_c0", 800 * MHZ, 1);
	return 0;
}
DEV_TREE_UPDATE(lk2nd_8953_clock_setup);
