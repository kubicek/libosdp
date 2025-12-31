/*
 * Copyright (c) 2020-2025 Siddharth Chandrasekaran <sidcha.dev@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "module.h"

VALUE mOSDP;
VALUE mOSDPSys;

static void rbosdp_add_module_constants(void)
{
	/* Setup flags */
	rb_define_const(mOSDPSys, "FLAG_ENFORCE_SECURE", INT2NUM(OSDP_FLAG_ENFORCE_SECURE));
	rb_define_const(mOSDPSys, "FLAG_INSTALL_MODE", INT2NUM(OSDP_FLAG_INSTALL_MODE));
	rb_define_const(mOSDPSys, "FLAG_IGN_UNSOLICITED", INT2NUM(OSDP_FLAG_IGN_UNSOLICITED));
	rb_define_const(mOSDPSys, "FLAG_ENABLE_NOTIFICATION", INT2NUM(OSDP_FLAG_ENABLE_NOTIFICATION));
	rb_define_const(mOSDPSys, "FLAG_CAPTURE_PACKETS", INT2NUM(OSDP_FLAG_CAPTURE_PACKETS));
	rb_define_const(mOSDPSys, "FLAG_ALLOW_EMPTY_ENCRYPTED_DATA_BLOCK", INT2NUM(OSDP_FLAG_ALLOW_EMPTY_ENCRYPTED_DATA_BLOCK));

	/* Log levels */
	rb_define_const(mOSDPSys, "LOG_EMERG", INT2NUM(OSDP_LOG_EMERG));
	rb_define_const(mOSDPSys, "LOG_ALERT", INT2NUM(OSDP_LOG_ALERT));
	rb_define_const(mOSDPSys, "LOG_CRIT", INT2NUM(OSDP_LOG_CRIT));
	rb_define_const(mOSDPSys, "LOG_ERROR", INT2NUM(OSDP_LOG_ERROR));
	rb_define_const(mOSDPSys, "LOG_WARNING", INT2NUM(OSDP_LOG_WARNING));
	rb_define_const(mOSDPSys, "LOG_NOTICE", INT2NUM(OSDP_LOG_NOTICE));
	rb_define_const(mOSDPSys, "LOG_INFO", INT2NUM(OSDP_LOG_INFO));
	rb_define_const(mOSDPSys, "LOG_DEBUG", INT2NUM(OSDP_LOG_DEBUG));
	rb_define_const(mOSDPSys, "LOG_MAX_LEVEL", INT2NUM(OSDP_LOG_MAX_LEVEL));

	/* enum osdp_cmd_e */
	rb_define_const(mOSDPSys, "CMD_OUTPUT", INT2NUM(OSDP_CMD_OUTPUT));
	rb_define_const(mOSDPSys, "CMD_LED", INT2NUM(OSDP_CMD_LED));
	rb_define_const(mOSDPSys, "CMD_BUZZER", INT2NUM(OSDP_CMD_BUZZER));
	rb_define_const(mOSDPSys, "CMD_TEXT", INT2NUM(OSDP_CMD_TEXT));
	rb_define_const(mOSDPSys, "CMD_COMSET", INT2NUM(OSDP_CMD_COMSET));
	rb_define_const(mOSDPSys, "CMD_COMSET_DONE", INT2NUM(OSDP_CMD_COMSET_DONE));
	rb_define_const(mOSDPSys, "CMD_KEYSET", INT2NUM(OSDP_CMD_KEYSET));
	rb_define_const(mOSDPSys, "CMD_MFG", INT2NUM(OSDP_CMD_MFG));
	rb_define_const(mOSDPSys, "CMD_FILE_TX", INT2NUM(OSDP_CMD_FILE_TX));
	rb_define_const(mOSDPSys, "CMD_STATUS", INT2NUM(OSDP_CMD_STATUS));

	rb_define_const(mOSDPSys, "STATUS_REPORT_LOCAL", INT2NUM(OSDP_STATUS_REPORT_LOCAL));
	rb_define_const(mOSDPSys, "STATUS_REPORT_INPUT", INT2NUM(OSDP_STATUS_REPORT_INPUT));
	rb_define_const(mOSDPSys, "STATUS_REPORT_OUTPUT", INT2NUM(OSDP_STATUS_REPORT_OUTPUT));
	rb_define_const(mOSDPSys, "STATUS_REPORT_REMOTE", INT2NUM(OSDP_STATUS_REPORT_REMOTE));

	/* For struct osdp_cmd_file_tx::flags */
	rb_define_const(mOSDPSys, "CMD_FILE_TX_FLAG_CANCEL", INT2NUM(OSDP_CMD_FILE_TX_FLAG_CANCEL));

	/* For struct osdp_event_notification::type */
	rb_define_const(mOSDPSys, "EVENT_NOTIFICATION_COMMAND", INT2NUM(OSDP_EVENT_NOTIFICATION_COMMAND));
	rb_define_const(mOSDPSys, "EVENT_NOTIFICATION_SC_STATUS", INT2NUM(OSDP_EVENT_NOTIFICATION_SC_STATUS));
	rb_define_const(mOSDPSys, "EVENT_NOTIFICATION_PD_STATUS", INT2NUM(OSDP_EVENT_NOTIFICATION_PD_STATUS));

	/* enum osdp_event_type */
	rb_define_const(mOSDPSys, "EVENT_CARDREAD", INT2NUM(OSDP_EVENT_CARDREAD));
	rb_define_const(mOSDPSys, "EVENT_KEYPRESS", INT2NUM(OSDP_EVENT_KEYPRESS));
	rb_define_const(mOSDPSys, "EVENT_MFGREP", INT2NUM(OSDP_EVENT_MFGREP));
	rb_define_const(mOSDPSys, "EVENT_STATUS", INT2NUM(OSDP_EVENT_STATUS));
	rb_define_const(mOSDPSys, "EVENT_NOTIFICATION", INT2NUM(OSDP_EVENT_NOTIFICATION));

	/* enum osdp_led_color_e */
	rb_define_const(mOSDPSys, "LED_COLOR_NONE", INT2NUM(OSDP_LED_COLOR_NONE));
	rb_define_const(mOSDPSys, "LED_COLOR_RED", INT2NUM(OSDP_LED_COLOR_RED));
	rb_define_const(mOSDPSys, "LED_COLOR_GREEN", INT2NUM(OSDP_LED_COLOR_GREEN));
	rb_define_const(mOSDPSys, "LED_COLOR_AMBER", INT2NUM(OSDP_LED_COLOR_AMBER));
	rb_define_const(mOSDPSys, "LED_COLOR_BLUE", INT2NUM(OSDP_LED_COLOR_BLUE));
	rb_define_const(mOSDPSys, "LED_COLOR_MAGENTA", INT2NUM(OSDP_LED_COLOR_MAGENTA));
	rb_define_const(mOSDPSys, "LED_COLOR_CYAN", INT2NUM(OSDP_LED_COLOR_CYAN));
	rb_define_const(mOSDPSys, "LED_COLOR_WHITE", INT2NUM(OSDP_LED_COLOR_WHITE));

	/* enum osdp_event_cardread_format_e */
	rb_define_const(mOSDPSys, "CARD_FMT_RAW_UNSPECIFIED", INT2NUM(OSDP_CARD_FMT_RAW_UNSPECIFIED));
	rb_define_const(mOSDPSys, "CARD_FMT_RAW_WIEGAND", INT2NUM(OSDP_CARD_FMT_RAW_WIEGAND));
	rb_define_const(mOSDPSys, "CARD_FMT_ASCII", INT2NUM(OSDP_CARD_FMT_ASCII));

	/* enum osdp_pd_cap_function_code_e */
	rb_define_const(mOSDPSys, "CAP_UNUSED", INT2NUM(OSDP_PD_CAP_UNUSED));
	rb_define_const(mOSDPSys, "CAP_CONTACT_STATUS_MONITORING", INT2NUM(OSDP_PD_CAP_CONTACT_STATUS_MONITORING));
	rb_define_const(mOSDPSys, "CAP_OUTPUT_CONTROL", INT2NUM(OSDP_PD_CAP_OUTPUT_CONTROL));
	rb_define_const(mOSDPSys, "CAP_CARD_DATA_FORMAT", INT2NUM(OSDP_PD_CAP_CARD_DATA_FORMAT));
	rb_define_const(mOSDPSys, "CAP_READER_LED_CONTROL", INT2NUM(OSDP_PD_CAP_READER_LED_CONTROL));
	rb_define_const(mOSDPSys, "CAP_READER_AUDIBLE_OUTPUT", INT2NUM(OSDP_PD_CAP_READER_AUDIBLE_OUTPUT));
	rb_define_const(mOSDPSys, "CAP_READER_TEXT_OUTPUT", INT2NUM(OSDP_PD_CAP_READER_TEXT_OUTPUT));
	rb_define_const(mOSDPSys, "CAP_TIME_KEEPING", INT2NUM(OSDP_PD_CAP_TIME_KEEPING));
	rb_define_const(mOSDPSys, "CAP_CHECK_CHARACTER_SUPPORT", INT2NUM(OSDP_PD_CAP_CHECK_CHARACTER_SUPPORT));
	rb_define_const(mOSDPSys, "CAP_COMMUNICATION_SECURITY", INT2NUM(OSDP_PD_CAP_COMMUNICATION_SECURITY));
	rb_define_const(mOSDPSys, "CAP_RECEIVE_BUFFERSIZE", INT2NUM(OSDP_PD_CAP_RECEIVE_BUFFERSIZE));
	rb_define_const(mOSDPSys, "CAP_LARGEST_COMBINED_MESSAGE_SIZE", INT2NUM(OSDP_PD_CAP_LARGEST_COMBINED_MESSAGE_SIZE));
	rb_define_const(mOSDPSys, "CAP_SMART_CARD_SUPPORT", INT2NUM(OSDP_PD_CAP_SMART_CARD_SUPPORT));
	rb_define_const(mOSDPSys, "CAP_READERS", INT2NUM(OSDP_PD_CAP_READERS));
	rb_define_const(mOSDPSys, "CAP_BIOMETRICS", INT2NUM(OSDP_PD_CAP_BIOMETRICS));
}

static VALUE rbosdp_set_loglevel(VALUE self, VALUE log_level)
{
	int level = NUM2INT(log_level);

	if (level < OSDP_LOG_EMERG || level > OSDP_LOG_MAX_LEVEL) {
		rb_raise(rb_eArgError, "invalid log level");
	}

	osdp_logger_init("rbosdp", level, NULL);

	return Qnil;
}

void Init_osdp_sys(void)
{
	mOSDP = rb_define_module("OSDP");
	mOSDPSys = rb_define_module_under(mOSDP, "Sys");

	rbosdp_add_module_constants();

	rb_define_module_function(mOSDPSys, "set_loglevel", rbosdp_set_loglevel, 1);

	Init_osdp_base();
	Init_osdp_cp();
	Init_osdp_pd();
}
