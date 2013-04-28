#ifndef __LINUX_MSM_CAMERA_QUERY_H_
#define __LINUX_MSM_CAMERA_QUERY_H_

struct otp_info_t {
	uint8_t otp_info[256];
};

struct af_info_t {
	uint16_t af_act_type;
	uint32_t af_man_type1;
	uint32_t af_man_type2;
};
extern struct af_info_t af_info;

#endif /* __LINUX_MSM_CAMERA_QUERY_H_ */
