/*
 * Copyright (c) 2020-2025 Siddharth Chandrasekaran <sidcha.dev@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "module.h"

#define TAG "rbosdp_data"

int rbosdp_make_struct_cmd(struct osdp_cmd *cmd, VALUE hash)
{
	/* Command conversion will be implemented when needed */
	return -1;
}

int rbosdp_make_hash_cmd(VALUE *hash, struct osdp_cmd *cmd)
{
	/* Command conversion will be implemented when needed */
	*hash = rb_hash_new();
	return 0;
}

int rbosdp_make_hash_event(VALUE *hash, struct osdp_event *event)
{
	/* Event conversion will be implemented when needed */
	*hash = rb_hash_new();
	return 0;
}

int rbosdp_make_struct_event(struct osdp_event *event, VALUE hash)
{
	/* Event conversion will be implemented when needed */
	return -1;
}

VALUE rbosdp_make_hash_pd_id(struct osdp_pd_id *pd_id)
{
	VALUE hash = rb_hash_new();

	/* PD ID conversion will be implemented when needed */
	return hash;
}
