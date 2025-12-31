/*
 * Copyright (c) 2020-2025 Siddharth Chandrasekaran <sidcha.dev@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "module.h"

#define TAG "rbosdp_cp"

void Init_osdp_cp(void)
{
	VALUE cControlPanel = rb_define_class_under(mOSDPSys, "ControlPanel", cOSDPBase);
	/* CP methods will be implemented in Ruby wrapper */
}
