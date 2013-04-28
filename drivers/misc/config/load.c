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

#include <linux/fcntl.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/ioctl.h>
#include <linux/stat.h>
#include <linux/types.h>
#include <linux/unistd.h>
#include "utags.h"
#include "utags_internal.h"

struct utag *load_utags(enum utag_error *pstatus)
{
  int res;
  size_t block_size;
  ssize_t bytes;
  struct utag *head = NULL;
  void *data;
  enum utag_error status = UTAG_NO_ERROR;
  int file_errno;
  struct file *filp = NULL;
  struct inode *inode = NULL;

  filp = filp_open(utags_blkdev, O_RDONLY, 0600);
  if (IS_ERR_OR_NULL(filp)) {
    file_errno = -PTR_ERR(filp);
    pr_err("%s ERROR opening file (%s) errno=%d\n", __func__,
          utags_blkdev, file_errno);
    status = UTAG_ERR_PARTITION_OPEN_FAILED;
    goto out;
  }

  if(filp->f_path.dentry)
    inode = filp->f_path.dentry->d_inode;
  if(!inode || !S_ISBLK(inode->i_mode)) {
    status = UTAG_ERR_PARTITION_NOT_BLKDEV;
    goto close_block;
  }

  res = filp->f_op->unlocked_ioctl(filp, BLKGETSIZE64, (unsigned long)&block_size);
  if (0 > res) {
    status = UTAG_ERR_PARTITION_NOT_BLKDEV;
    goto close_block;
  }

  data = kmalloc(block_size, GFP_KERNEL);
  if (!data) {
    status = UTAG_ERR_OUT_OF_MEMORY;
    goto close_block;
  }

  bytes = kernel_read(filp, filp->f_pos, data, block_size);
  if ((ssize_t)block_size > bytes) {
    status = UTAG_ERR_PARTITION_READ_ERR;
    goto free_data;
  }

  head = thaw_tags(block_size, data, &status);

free_data:
  kfree(data);

close_block:
  filp_close(filp, NULL);

out:
  if (pstatus) *pstatus = status;

  return head;
}
