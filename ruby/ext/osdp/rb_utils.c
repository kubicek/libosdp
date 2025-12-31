/*
 * Copyright (c) 2020-2025 Siddharth Chandrasekaran <sidcha.dev@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "module.h"
#include <string.h>

int rbosdp_hash_set_bool(VALUE hash, const char *key, bool val)
{
	rb_hash_aset(hash, ID2SYM(rb_intern(key)), val ? Qtrue : Qfalse);
	return 0;
}

int rbosdp_hash_set_int(VALUE hash, const char *key, int val)
{
	rb_hash_aset(hash, ID2SYM(rb_intern(key)), INT2NUM(val));
	return 0;
}

int rbosdp_hash_set_str(VALUE hash, const char *key, const char *val)
{
	rb_hash_aset(hash, ID2SYM(rb_intern(key)), rb_str_new_cstr(val));
	return 0;
}

int rbosdp_hash_set_bytes(VALUE hash, const char *key, const uint8_t *data, int len)
{
	rb_hash_aset(hash, ID2SYM(rb_intern(key)), rb_str_new((const char *)data, len));
	return 0;
}

int rbosdp_parse_int(VALUE obj, int *res)
{
	if (FIXNUM_P(obj) || TYPE(obj) == T_BIGNUM) {
		*res = NUM2INT(obj);
		return 0;
	}
	rb_raise(rb_eTypeError, "Expected integer");
	return -1;
}

/* NOTE: Caller must free the returned string with free() */
int rbosdp_parse_str(VALUE obj, char **str)
{
	if (TYPE(obj) != T_STRING) {
		rb_raise(rb_eTypeError, "Expected string");
		return -1;
	}

	*str = strdup(StringValueCStr(obj));
	if (*str == NULL) {
		rb_raise(rb_eNoMemError, "String allocation failed");
		return -1;
	}
	return 0;
}

int rbosdp_parse_bytes(VALUE obj, uint8_t **data, int *length, bool allow_empty)
{
	if (TYPE(obj) != T_STRING) {
		rb_raise(rb_eTypeError, "Expected string/bytes");
		return -1;
	}

	*length = RSTRING_LEN(obj);
	if (!allow_empty && *length == 0) {
		rb_raise(rb_eArgError, "Empty data not allowed");
		return -1;
	}

	*data = (uint8_t *)RSTRING_PTR(obj);
	return 0;
}

int rbosdp_hash_get_bool(VALUE hash, const char *key, bool *res)
{
	VALUE val;

	if (TYPE(hash) != T_HASH) {
		rb_raise(rb_eTypeError, "Expected hash");
		return -1;
	}

	val = rb_hash_aref(hash, ID2SYM(rb_intern(key)));
	if (NIL_P(val))
		return -1;

	*res = RTEST(val);
	return 0;
}

int rbosdp_hash_get_int(VALUE hash, const char *key, int *res)
{
	VALUE val;

	if (TYPE(hash) != T_HASH) {
		rb_raise(rb_eTypeError, "Expected hash");
		return -1;
	}

	val = rb_hash_aref(hash, ID2SYM(rb_intern(key)));
	if (NIL_P(val))
		return -1;

	return rbosdp_parse_int(val, res);
}

int rbosdp_hash_get_str(VALUE hash, const char *key, char **str)
{
	VALUE val;

	if (TYPE(hash) != T_HASH) {
		rb_raise(rb_eTypeError, "Expected hash");
		return -1;
	}

	val = rb_hash_aref(hash, ID2SYM(rb_intern(key)));
	if (NIL_P(val))
		return -1;

	return rbosdp_parse_str(val, str);
}

int rbosdp_hash_get_bytes(VALUE hash, const char *key, uint8_t **buf, int *len)
{
	VALUE val;

	if (TYPE(hash) != T_HASH) {
		rb_raise(rb_eTypeError, "Expected hash");
		return -1;
	}

	val = rb_hash_aref(hash, ID2SYM(rb_intern(key)));
	if (NIL_P(val))
		return -1;

	return rbosdp_parse_bytes(val, buf, len, false);
}

int rbosdp_hash_get_bytes_allow_empty(VALUE hash, const char *key, uint8_t **data, int *length)
{
	VALUE val;

	if (TYPE(hash) != T_HASH) {
		rb_raise(rb_eTypeError, "Expected hash");
		return -1;
	}

	val = rb_hash_aref(hash, ID2SYM(rb_intern(key)));
	if (NIL_P(val))
		return -1;

	return rbosdp_parse_bytes(val, data, length, true);
}

int rbosdp_hash_get_object(VALUE hash, const char *key, VALUE *obj)
{
	if (TYPE(hash) != T_HASH) {
		rb_raise(rb_eTypeError, "Expected hash");
		return -1;
	}

	*obj = rb_hash_aref(hash, ID2SYM(rb_intern(key)));
	if (NIL_P(*obj))
		return -1;

	return 0;
}

static int channel_send(void *data, uint8_t *buf, int len)
{
	VALUE channel = (VALUE)((uintptr_t)data);
	VALUE result;

	result = rb_funcall(channel, rb_intern("send"), 1, rb_str_new((const char *)buf, len));
	return NUM2INT(result);
}

static int channel_recv(void *data, uint8_t *buf, int len)
{
	VALUE channel = (VALUE)((uintptr_t)data);
	VALUE result;
	VALUE received_data;
	int received_len;

	result = rb_funcall(channel, rb_intern("recv"), 1, INT2NUM(len));
	if (NIL_P(result))
		return 0;

	if (TYPE(result) != T_STRING) {
		rb_raise(rb_eTypeError, "recv must return string or nil");
		return -1;
	}

	received_len = RSTRING_LEN(result);
	if (received_len > len)
		received_len = len;

	memcpy(buf, RSTRING_PTR(result), received_len);
	return received_len;
}

static void channel_flush(void *data)
{
	VALUE channel = (VALUE)((uintptr_t)data);

	rb_funcall(channel, rb_intern("flush"), 0);
}

void rbosdp_get_channel(VALUE channel, struct osdp_channel *ops)
{
	ops->data = (void *)((uintptr_t)channel);
	ops->send = channel_send;
	ops->recv = channel_recv;
	ops->flush = channel_flush;
}
