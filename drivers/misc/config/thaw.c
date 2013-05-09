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

#include <linux/inet.h>
#include <linux/string.h>
#include <linux/types.h>
#include "utags_internal.h"

struct utag *thaw_tags(size_t block_size, void *buf,
    enum utag_error *status)
{
  struct utag *head = NULL, *cur = NULL;
  uint8_t *ptr = buf;
  enum utag_error err = UTAG_NO_ERROR;

  /*
   * make sure the block is at least big enough to hold header
   * and footer
   */

  if (UTAG_MIN_TAG_SIZE*2 > block_size) {
    err = UTAG_ERR_NO_ROOM;
    goto out;
  }

  while(1) {
    struct frozen_utag *frozen;
    uint8_t *next_ptr;

    frozen = (struct frozen_utag *)ptr;

    if (!head) {
      cur = kcalloc(1, sizeof(struct utag), GFP_KERNEL);
      if (!cur) {
        err = UTAG_ERR_OUT_OF_MEMORY;
        goto out;
      }
    }

    cur->type = ntohl(frozen->type);
    cur->size = FROM_TAG_SIZE(ntohl(frozen->size));

    if (!head) {
      head = cur;

      if ((UTAG_HEAD != head->type) && (0 != head->size)) {
        err = UTAG_ERR_INVALID_HEAD;
        goto err_free;
      }
    }

    /* check if this is the end */
    if (UTAG_END == cur->type) {
      /* footer payload size should be zero */
      if (0 != cur->size) {
        err = UTAG_ERR_INVALID_TAIL;
        goto err_free;
      }

      /* finish up */
      cur->payload = NULL;
      cur->next = NULL;
      break;
    }

    next_ptr = ptr + UTAG_MIN_TAG_SIZE + cur->size;

    /*
     * Ensure there is enough space in the buffer for both the
     * payload and the tag header for the next tag.
     */
    if ((next_ptr-(uint8_t*)buf)+UTAG_MIN_TAG_SIZE > block_size) {
      err = UTAG_ERR_TAGS_TOO_BIG;
      goto err_free;
    }

    /*
     * Copy over the payload.
     */
    if (cur->size != 0) {
      cur->payload = kcalloc(1, cur->size, GFP_KERNEL);
      if (!cur->payload) {
        err = UTAG_ERR_OUT_OF_MEMORY;
        goto err_free;
      }
      memcpy(cur->payload, frozen->payload, cur->size);
    } else {
      cur->payload = NULL;
    }

    /* advance to beginning of next tag */
    ptr = next_ptr;

    /* get ready for the next tag */
    cur->next = kcalloc(1, sizeof(struct utag), GFP_KERNEL);
    cur = cur->next;
    if (!cur) {
      err = UTAG_ERR_OUT_OF_MEMORY;
      goto err_free;
    }
  }

  goto out;

err_free:
  free_tags(head);
  head = NULL;

out:
  if (status)
    *status = err;

  return head;
}
