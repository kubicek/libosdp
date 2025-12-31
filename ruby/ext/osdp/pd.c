/*
 * Copyright (c) 2020-2025 Siddharth Chandrasekaran <sidcha.dev@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "module.h"

#define TAG "rbosdp_pd"

void Init_osdp_pd(void)
{
	VALUE cPeripheralDevice = rb_define_class_under(mOSDPSys, "PeripheralDevice", cOSDPBase);
	/* PD methods will be implemented in Ruby wrapper */
}
