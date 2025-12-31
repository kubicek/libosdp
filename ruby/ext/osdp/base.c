/*
 * Copyright (c) 2020-2025 Siddharth Chandrasekaran <sidcha.dev@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "module.h"
#include <string.h>

#define TAG "rbosdp_base"

VALUE cOSDPBase;

int rbosdp_fops_open(void *arg, int file_id, int *size)
{
	int ret;
	rbosdp_base_t *self = arg;
	VALUE result;

	if (NIL_P(self->fops.open_cb))
		return -1;

	result = rb_funcall(self->fops.open_cb, rb_intern("call"), 2, INT2NUM(file_id), INT2NUM(*size));

	if (FIXNUM_P(result)) {
		ret = NUM2INT(result);
		self->file_id = file_id;
		*size = ret;
		return 0;
	}

	return -1;
}

int rbosdp_fops_read(void *arg, void *buf, int size, int offset)
{
	int len;
	rbosdp_base_t *self = arg;
	VALUE result;

	if (NIL_P(self->fops.read_cb))
		return -1;

	result = rb_funcall(self->fops.read_cb, rb_intern("call"), 2, INT2NUM(size), INT2NUM(offset));

	if (TYPE(result) == T_STRING) {
		len = RSTRING_LEN(result);
		if (len <= size) {
			memcpy(buf, RSTRING_PTR(result), len);
			return len;
		}
	}

	return -1;
}

int rbosdp_fops_write(void *arg, const void *buf, int size, int offset)
{
	int written;
	rbosdp_base_t *self = arg;
	VALUE data, result;

	if (NIL_P(self->fops.write_cb))
		return -1;

	data = rb_str_new((const char *)buf, size);
	result = rb_funcall(self->fops.write_cb, rb_intern("call"), 2, data, INT2NUM(offset));

	if (FIXNUM_P(result)) {
		written = NUM2INT(result);
		return written;
	}

	return -1;
}

int rbosdp_fops_close(void *arg)
{
	rbosdp_base_t *self = arg;

	if (NIL_P(self->fops.close_cb))
		return 0;

	rb_funcall(self->fops.close_cb, rb_intern("call"), 1, INT2NUM(self->file_id));

	return 0;
}

void Init_osdp_base(void)
{
	cOSDPBase = rb_define_class_under(mOSDPSys, "Base", rb_cObject);
}
