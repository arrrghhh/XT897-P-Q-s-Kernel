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
#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/unistd.h>
#include <asm/uaccess.h>
#include "utags.h"
#include "utags_internal.h"

enum utag_error store_utags(const struct utag *tags)
{
  int res;
  size_t written = 0;
  size_t block_size = 0, tags_size = 0;
  char *datap = NULL;
  enum utag_error status = UTAG_NO_ERROR;
  int file_errno;
  struct file *filep = NULL;
  struct inode *inode = NULL;
  mm_segment_t fs;

  fs = get_fs();
  set_fs(KERNEL_DS);

  filep = filp_open(utags_blkdev, O_RDWR, 0);
  if (IS_ERR_OR_NULL(filep)) {
    file_errno = -PTR_ERR(filep);
    pr_err("%s ERROR opening file (%s) errno=%d\n", __func__,
          utags_blkdev, file_errno);
    status = UTAG_ERR_PARTITION_OPEN_FAILED;
    goto out;
  }

  if(filep->f_path.dentry)
    inode = filep->f_path.dentry->d_inode;
  if(!inode || !S_ISBLK(inode->i_mode)) {
    status = UTAG_ERR_PARTITION_NOT_BLKDEV;
    goto close_block;
  }

  res = filep->f_op->unlocked_ioctl(filep, BLKGETSIZE64, (unsigned long) &block_size);
  if (0 > res) {
    status = UTAG_ERR_PARTITION_NOT_BLKDEV;
    goto close_block;
  }

  datap =  freeze_tags(block_size, tags, &tags_size, &status);
  if (!datap)
    goto close_block;

  written = filep->f_op->write(filep, datap, tags_size, &filep->f_pos);
  if (written < tags_size) {
    pr_err("%s ERROR writing file (%s) ret %d\n", __func__,
          utags_blkdev, written);
    status = UTAG_ERR_PARTITION_WRITE_ERR;
  }
  kfree(datap);

close_block:
  filp_close(filep, NULL);

out:
  set_fs(fs);
  return status;
}
