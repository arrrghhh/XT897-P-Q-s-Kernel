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

ssize_t find_first_utag(const struct utag *head, uint32_t type, void **payload,
    enum utag_error *pstatus)
{
  ssize_t size = -1;
  enum utag_error status = UTAG_ERR_NOT_FOUND;
  const struct utag *cur = head;

  if (!payload || !cur) {
    status = UTAG_ERR_INVALID_ARGS;
    goto out;
  }

  while(cur) {
    if (cur->type == type) {
      *payload = (void *)cur->payload;
      size = (ssize_t)cur->size;
      status = UTAG_NO_ERROR;
      goto out;
    }

    cur = cur->next;
  }

out:
  if (pstatus) *pstatus = status;

  return size;
}
