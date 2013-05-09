#!/bin/bash
[ $# -eq 0 ] && { echo "Usage:
	 $0 Kernel-name [Stock,CM,CM101]"; exit 1; }

    # These setup our build enviroment
    THREADS=$(expr 4 + $(grep processor /proc/cpuinfo | wc -l))
    DEFCONFIG=msm8960_mmi_defconfig
    ARCH="ARCH=arm"
    CROSS="CROSS_COMPILE=/media/raid/dev/trees/prebuilt/linux-x86/toolchain/arm-eabi-4.4.3/bin/arm-eabi-"
#    CROSS="CROSS_COMPILE=/home/arrrghhh/toolchain/google/linux-x86/toolchain/arm-eabi-4.4.3/bin/arm-eabi-"
#    CROSS="CROSS_COMPILE=/home/arrrghhh/toolchain/linaro/android-toolchain-eabi_4.6-2012.07/bin/arm-eabi-"
    # Setup our directories now
    DIR=/media/raid/dev/trees/XT897-P-Q-s-Kernel
    TOOLS=/media/raid/dev/kernel/Tools
    KERNEL=$DIR
    PACK=$KERNEL/package
    OUT=$KERNEL/arch/arm/boot

    # These are extra variables designed to make things easier
    MODULES=$TOOLS/Updater-Scripts/XT897/system/lib/modules
    KERNELNAME=$1

    # Set our Ramdisk locations (uncomment teh CM ones when you actually need them :) )
    RAMDISK=/media/raid/dev/kernel/ramdisk
    #CMRAMDISK=~/xt897/Ramdisks/XT897-CM
    #CM101RAMDISK=~/xt897/Ramdisks/XT897-CM10-1

    # These are for mkbootimg
    BASE="--base 0x80200000"
    PAGE="--pagesize 2048"
    RAMADDR="--ramdiskaddr 0x81600000"
#    CMDLINE='--cmdline "console=/dev/null androidboot.hardware=qcom user_debug=31 loglevel=1 msm_rtb.filter=0x3F kgsl.mmutype=gpummu"'

    # Edit this to change the kernel name
    KBUILD_BUILD_VERSION=$1
    export KBUILD_BUILD_VERSION

    MAKE="make -j${THREADS}"
    export USE_CCACHE=1
    export $ARCH
    export $CROSS

    # This cleans out crud and makes new config
    $MAKE clean
    $MAKE mrproper
    rm -rf $MODULES
    rm -rf $PACK
    [ -d "$PACK" ] || mkdir "$PACK"
    [ -d "$MODULES" ] || mkdir -p "$MODULES"
#    exec > >(tee $PACK/buildlog.txt) 2>&1 
    $MAKE $DEFCONFIG

#    echo "All clean!" > $LOG
#    date >> $LOG
#    echo "" >> $LOG

    # Finally making the kernel
    $MAKE zImage 2>&1 | tee /var/www/logs/kernelbuildlog.txt
    $MAKE modules

#    echo "Compiled" >> $LOG
#    date >> $LOG
#    echo "" >> $LOG

    if [ -f $OUT/zImage ]; then
          echo
          echo "Kernel has been compiled!!! You can find it in arch/arm/boot/zImage"
          echo
     else
          echo
          echo "Kernel did not compile, please check for errors!!"
          echo
          exit
    fi

    # These move files to easier locations
    find -name '*.ko' -exec cp -av {} $MODULES/ \;

    # This part packs the img up :)
    # In order for this part to work you need the mkbootimg tools
# -----------------------------------------------------------------------------------------------
    cd $PACK
	cp $OUT/zImage $PACK
	$TOOLS/mkbootfs $RAMDISK | gzip > $PACK/ramdisk.gz
	$TOOLS/mkbootimg --cmdline "console=/dev/null androidboot.hardware=qcom user_debug=31 loglevel=1 msm_rtb.filter=0x3F kgsl.mmutype=gpummu" --kernel $PACK/zImage --ramdisk $PACK/ramdisk.gz $PAGE $BASE $RAMADDR -o $PACK/boot.img
	rm -rf ramdisk.gz
	rm -rf zImage
	cp -R $TOOLS/Updater-Scripts/XT897/* $PACK
	zip -r $KERNELNAME"-Stock.zip" *
# -----------------------------------------------------------------------------------------------
# All Done
    echo $KERNELNAME"-"$2 "was made!"
#    echo "packed" >> $LOG
#    date >> $LOG
