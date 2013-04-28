/* Copyright (c) 2012, Motorola Mobility. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "utags.h"

#ifndef __UTAGS_INTERNAL_H_HEADER__
#define __UTAGS_INTERNAL_H_HEADER__

#define TO_TAG_SIZE(n)      (((n)+3)>>2)
#define FROM_TAG_SIZE(n)    ((n)<<2)

struct frozen_utag {
	uint32_t	type;
	uint32_t	size;
	uint8_t		payload[];
};

/* comes out to 8 since payload is empty array */
#define UTAG_MIN_TAG_SIZE   (sizeof(struct frozen_utag))

extern const char *utags_blkdev;

#define UTAGS_PARTITION "/dev/block/platform/msm_sdcc.1/by-name/utags"

#endif
