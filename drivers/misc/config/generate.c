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

struct utag *generate_empty_tags(void)
{
  struct utag *head, *cur;

  cur = head = kmalloc(sizeof(struct utag), GFP_KERNEL);

  if (!cur)
    return NULL;

  cur->type = UTAG_HEAD;
  cur->size = 0;
  cur->payload = NULL;
  cur->next = kmalloc(sizeof(struct utag), GFP_KERNEL);

  cur = cur->next;

  if (!cur) {
    kfree(head);
    return NULL;
  }

  cur->type = UTAG_END;
  cur->size = 0;
  cur->payload = NULL;
  cur->next = NULL;

  return head;
}
