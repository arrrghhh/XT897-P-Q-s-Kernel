/* Copyright (c) 2008-2012, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef DIAGFWD_H
#define DIAGFWD_H

#define NO_PROCESS	0
#define NON_APPS_PROC	-1

//Slate code starts IKASANTISPRINT-207
//#define SLATE_DEBUG
#define DIAG_MASK_CMD_SAVE                           0
#define DIAG_MASK_CMD_RESTORE                        1
#define DIAG_MASK_CMD_ADD_GET_RSSI                   2
#define DIAG_MASK_CMD_ADD_GET_STATE_AND_CONN_ATT     3
#define DIAG_MASK_CMD_ADD_GET_SEARCHER_DUMP          4
#define DIAG_LOG_CMD_TYPE_NONE                    0
#define DIAG_LOG_CMD_TYPE_GET_RSSI                1
#define DIAG_LOG_CMD_TYPE_GET_STATE_AND_CONN_ATT  2
#define DIAG_LOG_CMD_TYPE_RESTORE_LOG_MASKS       3
#define DIAG_LOG_CMD_TYPE_GET_1x_SEARCHER_DUMP    4
#define DIAG_LOG_TYPE_RSSI                        0
#define DIAG_LOG_TYPE_STATE                       1
#define DIAG_LOG_TYPE_CONN_ATT                    2
//Slate code end

void diagfwd_init(void);
void diagfwd_exit(void);
void diag_process_hdlc(void *data, unsigned len);
void __diag_smd_send_req(void);
void __diag_smd_qdsp_send_req(void);
void __diag_smd_wcnss_send_req(void);
void diag_legacy_notifier(void *, unsigned, struct diag_request *);
long diagchar_ioctl(struct file *, unsigned int, unsigned long);
int diag_device_write(void *, int, struct diag_request *);
int mask_request_validate(unsigned char mask_buf[]);
void diag_clear_reg(int);
int chk_apps_only(void);
void diag_send_event_mask_update(smd_channel_t *, int num_bytes);
void diag_send_msg_mask_update(smd_channel_t *, int ssid_first,
					 int ssid_last, int proc);
void diag_send_log_mask_update(smd_channel_t *, int);
/* State for diag forwarding */
#if defined(CONFIG_DIAG_OVER_USB) || defined(CONFIG_DIAG_INTERNAL)
int diagfwd_connect(void);
int diagfwd_disconnect(void);
struct legacy_diag_ch *channel_diag_open(const char *name, void *priv,
		void (*notify)(void *, unsigned, struct diag_request *));
void channel_diag_close(struct legacy_diag_ch *ch);
int channel_diag_read(struct legacy_diag_ch *ch, struct diag_request *d_req);
int channel_diag_write(struct legacy_diag_ch *ch, struct diag_request *d_req);
#endif
extern int diag_debug_buf_idx;
extern unsigned char diag_debug_buf[1024];
extern int diag_event_num_bytes;

//Slate code starts IKASANTISPRINT-207
void diag_process_get_rssi_log(void);
void diag_process_get_stateAndConnInfo_log(void);
int  diag_log_is_enabled(unsigned char log_type);
void diag_cfg_event_mask(void);
//Slate code end

#endif
