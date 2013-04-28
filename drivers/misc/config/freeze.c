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

void *freeze_tags(size_t block_size, const struct utag *tags,
    size_t *tags_size, enum utag_error *status)
{
  size_t frozen_size = 0;
  char *buf = NULL, *ptr;
  const struct utag *cur = tags;
  enum utag_error err = UTAG_NO_ERROR;

  /* Make sure the tags start with the HEAD marker. */
  if (tags && (UTAG_HEAD != tags->type)) {
    err = UTAG_ERR_INVALID_HEAD;
    goto out;
  }

  /*
   * Walk the list once to determine the amount of space to allocate
   * for the frozen tags.
   */
  while (cur) {
    frozen_size += FROM_TAG_SIZE(TO_TAG_SIZE(cur->size))
      + UTAG_MIN_TAG_SIZE;

    if (UTAG_END == cur->type)
      break;

    cur = cur->next;
  }

  /* do some more sanity checking */
  if (((cur) && (cur->next)) || (!cur)) {
    err = UTAG_ERR_INVALID_TAIL;
    goto out;
  }

  if (block_size < frozen_size) {
    err = UTAG_ERR_TAGS_TOO_BIG;
    goto out;
  }

  ptr = buf = kmalloc(frozen_size, GFP_KERNEL);
  if (!buf) {
    err = UTAG_ERR_OUT_OF_MEMORY;
    goto out;
  }

  cur = tags;
  while (1) {
    size_t aligned_size, zeros;
    struct frozen_utag frozen;

    aligned_size = FROM_TAG_SIZE(TO_TAG_SIZE(cur->size));

    frozen.type = htonl(cur->type);
    frozen.size = htonl(TO_TAG_SIZE(cur->size));

    memcpy(ptr, &frozen, UTAG_MIN_TAG_SIZE);
    ptr += UTAG_MIN_TAG_SIZE;

    if (0 != cur->size) {
      memcpy(ptr, cur->payload, cur->size);

      ptr += cur->size;
    }

    /* pad with zeros if needed */
    zeros = aligned_size - cur->size;
    if(zeros) {
      memset(ptr, 0, zeros);
      ptr += zeros;
    }

    if (UTAG_END == cur->type)
      break;

    cur = cur->next;
  }

  if(tags_size)
    *tags_size = frozen_size;

out:
  if (status)
    *status = err;

  return buf;
}
