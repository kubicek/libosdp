/*
 * Copyright (c) 2020-2025 Siddharth Chandrasekaran <sidcha.dev@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _RBOSDP_H_
#define _RBOSDP_H_

#include <ruby.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

#include <utils/utils.h>
#include <osdp.h>

typedef struct {
	bool is_cp;

	int file_id;
	struct {
		VALUE open_cb;
		VALUE read_cb;
		VALUE write_cb;
		VALUE close_cb;
	} fops;
} rbosdp_base_t;

typedef struct {
	rbosdp_base_t base;
	VALUE event_cb;
	int num_pd;
	osdp_t *ctx;
	char *name;
} rbosdp_cp_t;

typedef struct {
	rbosdp_base_t base;
	VALUE command_cb;
	osdp_t *ctx;
	char *name;
} rbosdp_pd_t;

/* from utils.c */
int rbosdp_parse_int(VALUE obj, int *res);
int rbosdp_parse_str(VALUE obj, char **str);
int rbosdp_parse_bytes(VALUE obj, uint8_t **data, int *length, bool allow_empty);

int rbosdp_hash_get_bool(VALUE hash, const char *key, bool *res);
int rbosdp_hash_get_int(VALUE hash, const char *key, int *res);
int rbosdp_hash_get_str(VALUE hash, const char *key, char **str);
int rbosdp_hash_get_bytes(VALUE hash, const char *key, uint8_t **buf, int *len);
int rbosdp_hash_get_bytes_allow_empty(VALUE hash, const char *key, uint8_t **data, int *length);
int rbosdp_hash_get_object(VALUE hash, const char *key, VALUE *obj);

int rbosdp_hash_set_bool(VALUE hash, const char *key, bool val);
int rbosdp_hash_set_int(VALUE hash, const char *key, int val);
int rbosdp_hash_set_str(VALUE hash, const char *key, const char *val);
int rbosdp_hash_set_bytes(VALUE hash, const char *key, const uint8_t *data, int len);

void rbosdp_get_channel(VALUE channel, struct osdp_channel *ops);

/* from base.c */
extern VALUE cOSDPBase;
void Init_osdp_base(void);

/* from cp.c */
void Init_osdp_cp(void);

/* from pd.c */
void Init_osdp_pd(void);

/* from data.c */
int rbosdp_make_struct_cmd(struct osdp_cmd *cmd, VALUE hash);
int rbosdp_make_hash_cmd(VALUE *hash, struct osdp_cmd *cmd);
int rbosdp_make_hash_event(VALUE *hash, struct osdp_event *event);
int rbosdp_make_struct_event(struct osdp_event *event, VALUE hash);
VALUE rbosdp_make_hash_pd_id(struct osdp_pd_id *pd_id);

#endif /* _RBOSDP_H_ */
