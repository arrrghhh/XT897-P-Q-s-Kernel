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

#include <linux/miscdevice.h>
#include <linux/platform_device.h>
#include <linux/types.h>
#include <linux/input.h>
#include <linux/uaccess.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include "utags.h"

#define MAX_UTAG_SIZE 1024

struct proc_dir_entry *dir_root;
static char payload[MAX_UTAG_SIZE];
static uint32_t csum;

static struct utag_node utag_tab[] =
{
	{UTAG_DT_NAME, 		"dtname",	NULL, NULL, NULL, NULL},
	{UTAG_SERIALNO,		"barcode",	NULL, NULL, NULL, NULL},
	{UTAG_FTI,      	"fti",		NULL, NULL, NULL, NULL},
	{UTAG_MSN,       	"msn",		NULL, NULL, NULL, NULL},
	{UTAG_MODELNO,    	"model",	NULL, NULL, NULL, NULL},
	{UTAG_CARRIER,    	"carrier",	NULL, NULL, NULL, NULL},
	{UTAG_KERNEL_LOG_SWITCH, "log_switch",	NULL, NULL, NULL, NULL},
	{UTAG_BASEBAND,   	"baseband",	NULL, NULL, NULL, NULL},
	{UTAG_DISPLAY,    	"display",	NULL, NULL, NULL, NULL},
	{UTAG_BOOTMODE,   	"bootmode",	NULL, NULL, NULL, NULL},
	{UTAG_END,   		"all",		NULL, NULL, NULL, NULL},
	{0,			"",		NULL, NULL, NULL, NULL},
};


static char *find_name(uint32_t type)
{
	int i = 0;

	while (UTAG_END != utag_tab[i].type){
		if(type == utag_tab[i].type)
			return utag_tab[i].name;
		i++;
	}
	return "";

}


static int  proc_dump_tags (struct seq_file *file)
{
	int i;
	char *data = NULL;
	struct utag *tags = NULL;
	enum utag_error status;
	uint32_t loc_csum = 0;
	int count = 0;
	int bytes = 0;

	tags = load_utags(&status);
	if (NULL==tags)
		pr_err("%s Load config failed\n", __func__);
	else while(tags != NULL) {
		seq_printf(file, "Tag: Type: [0x%08X] Name [%s] Size: [0x%08X]\nData:\n\t",
			tags->type, find_name(tags->type), tags->size);
			bytes += tags->size;
		for(i=0, data=tags->payload; i < tags->size; i++) {
			loc_csum += data[i];
			seq_printf(file,"[0x%02X] ", data[i]);
			if((i+1)%10 == 0)
				seq_printf(file, "\n\t");
		}
		seq_printf(file, "\n\n");
		tags = tags->next;
		count++;
	}
	seq_printf(file, "Tag count %d old cs %#x new cs %#x bytes %d\n",
		count, csum, loc_csum, bytes);
	csum = loc_csum;
	free_tags(tags);
	return 0;
}

static int  read_tag (struct seq_file *file, void *v)
{
	int i;
	struct utag *tags = NULL;
	enum utag_error status;
	uint8_t *buf;
	ssize_t size;
	struct proc_node *proc = (struct  proc_node *) file->private;
	struct utag_node *mytag = proc->tag;
	uint32_t type = mytag->type;

	if (UTAG_END == type) {
		proc_dump_tags (file);
		return 0;
	}

	tags = load_utags(&status);
	if (NULL==tags) {
		pr_err("%s Load config failed\n", __func__);
		return -EFAULT;
	} else {
		size = find_first_utag(tags, type, (void**)&buf, &status);
		if (0 > size) {
			if (UTAG_ERR_NOT_FOUND == status)
				pr_err("Tag 0x%08X not found.\n", type);
			else
				pr_err("Unexpected error looking for tag: %d\n", status);
			free_tags(tags);
			return 11;
		}
		switch (proc->mode) {
			case OUT_ASCII:
				seq_printf(file, "%s\n", buf);
			break;
			case OUT_RAW:
				for(i = 0; i < size; i++) {
					seq_printf(file, "%02X", buf[i]);
				}
				seq_printf(file, "\n");
			break;
			case OUT_ID:
				seq_printf(file, "%#X\n", type);
			break;
		}
	}

	free_tags(tags);
	return 0;
}

static ssize_t write_tag (struct file *file, const char __user *buffer,
	size_t count, loff_t *pos)
{
	struct utag *tags = NULL;
	enum utag_error status;
	struct inode *inode = file->f_dentry->d_inode;
	struct proc_node *proc = (struct  proc_node *) PDE(inode)->data;
	struct utag_node *mytag = proc->tag;
	uint32_t type = mytag->type;

	if(UTAG_END == type)
		return count;

	if (MAX_UTAG_SIZE < count) {
		pr_err("%s error utag too big %d\n", __func__, count);
		return count;
	}

	if (copy_from_user(payload, buffer, count)){
		pr_err("%s user copy error\n", __func__);
		return count;
	}

	tags = load_utags(&status);
	if (NULL==tags) {
		pr_err("%s load config error\n", __func__);
		return count;
	} else {
		status = replace_first_utag(tags, type, payload, (count-1));
		if (UTAG_NO_ERROR != status)
			pr_err("%s error on update tag %#x status %d\n",
				__func__, type, status);
		else {
			status = store_utags(tags);
			if (UTAG_NO_ERROR != status)
				pr_err("%s error on store tags %#x status %d\n",
					__func__, type, status);
		}
	}

	free_tags(tags);
	return count;
}

static int config_read(struct inode *inode, struct file *file)
{
	return single_open(file, read_tag, PDE(inode)->data);
}

static const struct file_operations config_fops = {
	.owner = THIS_MODULE,
	.open = config_read,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
	.write = write_tag,
};

static int __init config_init(void)
{
	int i = 0;
	struct utag_node *utag = &utag_tab[0];
	struct proc_node *proc_data = NULL;
	dir_root = proc_mkdir("config", NULL);
	if (!dir_root) {
		pr_info("%s Failed to create dir entry\n", __func__);
		return -EFAULT;
	}
	while (UTAG_END != utag->type) {
		utag->root = proc_mkdir(utag->name, dir_root);
		utag->ascii_file = create_proc_entry("ascii", 0, utag->root);
		if (utag->ascii_file) {
			utag->ascii_file->proc_fops = &config_fops;
			proc_data = kmalloc(sizeof(struct proc_node), GFP_KERNEL);
			if(proc_data) {
				proc_data->mode = OUT_ASCII;
				proc_data->tag = utag;
				utag->ascii_file->data = (void *) proc_data;
			}
		}
		utag->raw_file = create_proc_entry("raw", 0, utag->root);
		if (utag->raw_file) {
			utag->raw_file->proc_fops = &config_fops;
			proc_data = kmalloc(sizeof(struct proc_node), GFP_KERNEL);
			if(proc_data) {
				proc_data->mode = OUT_RAW;
				proc_data->tag = utag;
				utag->raw_file->data = (void *) proc_data;
			}
		}
		utag->id_file = create_proc_entry("id", 0, utag->root);
		if (utag->id_file) {
			utag->id_file->proc_fops = &config_fops;
			proc_data = kmalloc(sizeof(struct proc_node), GFP_KERNEL);
			if(proc_data) {
				proc_data->mode = OUT_ID;
				proc_data->tag = utag;
				utag->id_file->data = (void *) proc_data;
			}
		}
		i++;
		utag = &utag_tab[i];
	}
	utag->raw_file = create_proc_entry(utag->name, 0, dir_root);
	if (utag->raw_file) {
			utag->raw_file->proc_fops = &config_fops;
			proc_data = kmalloc(sizeof(struct proc_node), GFP_KERNEL);
			if(proc_data) {
				proc_data->mode = OUT_RAW;
				proc_data->tag = utag;
				utag->raw_file->data = (void *) proc_data;
			}
	}
	return 0;
}

static void __exit config_exit(void)
{
	int i = 0;
	struct utag_node *utag = &utag_tab[0];
	while (UTAG_END != utag->type) {
		if(NULL != utag->ascii_file)
			remove_proc_entry("ascii", utag->root);
		if(NULL != utag->raw_file)
			remove_proc_entry("raw", utag->root);
		if(NULL != utag->id_file)
			remove_proc_entry("id", utag->root);
		remove_proc_entry(utag->name, dir_root);
		i++;
		utag = &utag_tab[i];
	}
	remove_proc_entry(utag->name, dir_root);
	remove_proc_entry("config", NULL);
}

module_init(config_init);
module_exit(config_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Motorola Mobility");
MODULE_DESCRIPTION("Configuration module");
