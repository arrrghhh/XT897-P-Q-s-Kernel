DEFCONFIGSRC			:= kernel/arch/arm/configs
LJAPDEFCONFIGSRC		:= ${DEFCONFIGSRC}/ext_config
PRODUCT_SPECIFIC_DEFCONFIGS	:= $(DEFCONFIGSRC)/$(KERNEL_DEFCONFIG)
_TARGET_DEFCONFIG		:= __ext_mapphone_defconfig
TARGET_DEFCONFIG		:= $(DEFCONFIGSRC)/$(_TARGET_DEFCONFIG)

# build eng kernel for eng and userdebug Android variants
ifneq ($(TARGET_BUILD_VARIANT), user)
PRODUCT_SPECIFIC_DEFCONFIGS += ${LJAPDEFCONFIGSRC}/eng_bld.config
endif

#
# make combined defconfig file
#---------------------------------------
$(TARGET_DEFCONFIG): FORCE $(PRODUCT_SPECIFIC_DEFCONFIGS)
	( perl -le 'print "# This file was automatically generated from:\n#\t" . join("\n#\t", @ARGV) . "\n"' $(PRODUCT_SPECIFIC_DEFCONFIGS) && cat $(PRODUCT_SPECIFIC_DEFCONFIGS) ) > $(TARGET_DEFCONFIG) || ( rm -f $@ && false )

.PHONY: FORCE
FORCE:
