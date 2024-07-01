/*
 * Copyright (c) 2024 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr/kernel.h>
// #include <zephyr/logging/log.h>
// LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

int main(void)
{
	// LOG_INF("Hello world!");

	for(;;){
		k_sleep(K_MSEC(500));
	}

	return 0;
}
