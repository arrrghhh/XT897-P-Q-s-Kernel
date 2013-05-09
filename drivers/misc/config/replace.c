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

#include <linux/string.h>
#include "utags.h"

enum utag_error replace_first_utag(struct utag *head, uint32_t type,
    const void *payload, size_t size)
{
  struct utag *cur = head;

  /* search for the first occurrence of specified type of tag */
  while (cur) {
    if (cur->type == type) {
      void *oldpayload = cur->payload;

      cur->payload = kmalloc(size, GFP_KERNEL);
      if (!cur->payload) {
        cur->payload = oldpayload;
        return UTAG_ERR_OUT_OF_MEMORY;
      }

      memcpy(cur->payload, payload, size);

      cur->size = size;

      if (oldpayload)
        kfree(oldpayload);

      return UTAG_NO_ERROR;
    }

    cur = cur->next;
  }

  /*
   * If specified type wasn't found, insert a new tag immediately after
   * the head.
   */
  cur = kmalloc(sizeof(struct utag), GFP_KERNEL);
  if (!cur)
    return UTAG_ERR_OUT_OF_MEMORY;

  cur->type = type;
  cur->size = size;
  cur->payload = kmalloc(size, GFP_KERNEL);
  if (!cur->payload) {
    kfree(cur);
    return UTAG_ERR_OUT_OF_MEMORY;
  }

  memcpy(cur->payload, payload, size);

  cur->next = head->next;
  head->next = cur;

  return UTAG_NO_ERROR;
}
