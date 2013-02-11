cmd_arch/arm/mach-msm/gpiomux-v2.o := /home/arrrghhh/trees/kernel/asa-14/scripts/gcc-wrapper.py /home/arrrghhh/cm10.1/prebuilt/linux-x86/toolchain/arm-eabi-4.4.3/bin/arm-eabi-gcc -Wp,-MD,arch/arm/mach-msm/.gpiomux-v2.o.d  -nostdinc -isystem /home/arrrghhh/cm10.1/prebuilt/linux-x86/toolchain/arm-eabi-4.4.3/bin/../lib/gcc/arm-eabi/4.4.3/include -I/home/arrrghhh/trees/kernel/asa-14/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-msm/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -marm -fno-dwarf2-cfi-asm -fstack-protector -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1024 -fomit-frame-pointer -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(gpiomux_v2)"  -D"KBUILD_MODNAME=KBUILD_STR(gpiomux_v2)" -c -o arch/arm/mach-msm/.tmp_gpiomux-v2.o arch/arm/mach-msm/gpiomux-v2.c

source_arch/arm/mach-msm/gpiomux-v2.o := arch/arm/mach-msm/gpiomux-v2.c

deps_arch/arm/mach-msm/gpiomux-v2.o := \
  include/linux/bitops.h \
  /home/arrrghhh/trees/kernel/asa-14/arch/arm/include/asm/types.h \
  include/asm-generic/int-ll64.h \
  /home/arrrghhh/trees/kernel/asa-14/arch/arm/include/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
    $(wildcard include/config/64bit.h) \
  /home/arrrghhh/trees/kernel/asa-14/arch/arm/include/asm/bitops.h \
    $(wildcard include/config/smp.h) \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
  /home/arrrghhh/trees/kernel/asa-14/arch/arm/include/asm/system.h \
    $(wildcard include/config/cpu/32v6k.h) \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/fa526.h) \
    $(wildcard include/config/arch/has/barriers.h) \
    $(wildcard include/config/arm/dma/mem/bufferable.h) \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/sa110.h) \
    $(wildcard include/config/cpu/v6.h) \
  include/linux/linkage.h \
  /home/arrrghhh/trees/kernel/asa-14/arch/arm/include/asm/linkage.h \
  include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  include/linux/typecheck.h \
  /home/arrrghhh/trees/kernel/asa-14/arch/arm/include/asm/irqflags.h \
  /home/arrrghhh/trees/kernel/asa-14/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/arm/thumb.h) \
  /home/arrrghhh/trees/kernel/asa-14/arch/arm/include/asm/hwcap.h \
  include/linux/stddef.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
  include/linux/posix_types.h \
  /home/arrrghhh/trees/kernel/asa-14/arch/arm/include/asm/posix_types.h \
  /home/arrrghhh/trees/kernel/asa-14/arch/arm/include/asm/outercache.h \
    $(wildcard include/config/outer/cache/sync.h) \
    $(wildcard include/config/outer/cache.h) \
  include/asm-generic/cmpxchg-local.h \
  include/asm-generic/bitops/non-atomic.h \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/arch_hweight.h \
  include/asm-generic/bitops/const_hweight.h \
  include/asm-generic/bitops/lock.h \
  include/asm-generic/bitops/le.h \
  /home/arrrghhh/trees/kernel/asa-14/arch/arm/include/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/linux/swab.h \
  /home/arrrghhh/trees/kernel/asa-14/arch/arm/include/asm/swab.h \
  include/linux/byteorder/generic.h \
  include/linux/io.h \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/has/ioport.h) \
  /home/arrrghhh/trees/kernel/asa-14/arch/arm/include/asm/io.h \
  /home/arrrghhh/trees/kernel/asa-14/arch/arm/include/asm/memory.h \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/dram/size.h) \
    $(wildcard include/config/dram/base.h) \
    $(wildcard include/config/have/tcm.h) \
    $(wildcard include/config/arm/patch/phys/virt.h) \
    $(wildcard include/config/arm/patch/phys/virt/16bit.h) \
  include/linux/const.h \
  arch/arm/mach-msm/include/mach/memory.h \
    $(wildcard include/config/phys/offset.h) \
    $(wildcard include/config/arch/msm7x30.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/vmsplit/3g.h) \
    $(wildcard include/config/arch/msm/arm11.h) \
    $(wildcard include/config/arch/msm/cortex/a5.h) \
    $(wildcard include/config/cache/l2x0.h) \
    $(wildcard include/config/arch/msm8x60.h) \
    $(wildcard include/config/arch/msm8960.h) \
    $(wildcard include/config/dont/map/hole/after/membank0.h) \
    $(wildcard include/config/dont/map/hole/in/lowmem.h) \
    $(wildcard include/config/arch/msm/scorpion.h) \
    $(wildcard include/config/arch/msm/krait.h) \
    $(wildcard include/config/arch/msm7x27.h) \
  /home/arrrghhh/trees/kernel/asa-14/arch/arm/include/asm/setup.h \
    $(wildcard include/config/bootinfo.h) \
  /home/arrrghhh/trees/kernel/asa-14/arch/arm/include/asm/sizes.h \
  include/asm-generic/sizes.h \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
  arch/arm/mach-msm/include/mach/msm_rtb.h \
    $(wildcard include/config/msm/rtb.h) \
  arch/arm/mach-msm/include/mach/io.h \
  /home/arrrghhh/trees/kernel/asa-14/arch/arm/include/asm/page.h \
    $(wildcard include/config/cpu/copy/v3.h) \
    $(wildcard include/config/cpu/copy/v4wt.h) \
    $(wildcard include/config/cpu/copy/v4wb.h) \
    $(wildcard include/config/cpu/copy/feroceon.h) \
    $(wildcard include/config/cpu/copy/fa.h) \
    $(wildcard include/config/cpu/xscale.h) \
    $(wildcard include/config/cpu/copy/v6.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
    $(wildcard include/config/memory/hotplug/sparse.h) \
  /home/arrrghhh/trees/kernel/asa-14/arch/arm/include/asm/glue.h \
  include/asm-generic/getorder.h \
  arch/arm/mach-msm/include/mach/msm_iomap.h \
    $(wildcard include/config/arch/apq8064.h) \
    $(wildcard include/config/arch/msm8930.h) \
    $(wildcard include/config/arch/msm9615.h) \
    $(wildcard include/config/arch/msmcopper.h) \
    $(wildcard include/config/arch/qsd8x50.h) \
    $(wildcard include/config/arch/fsm9xxx.h) \
    $(wildcard include/config/debug/msm/uart1.h) \
    $(wildcard include/config/debug/msm/uart2.h) \
    $(wildcard include/config/debug/msm/uart3.h) \
  arch/arm/mach-msm/include/mach/msm_iomap-8960.h \
    $(wildcard include/config/debug/msm8960/uart.h) \
  arch/arm/mach-msm/include/mach/msm_iomap-8930.h \
    $(wildcard include/config/debug/msm8930/uart.h) \
  arch/arm/mach-msm/include/mach/msm_iomap-8064.h \
  arch/arm/mach-msm/include/mach/msm_iomap-9615.h \
  arch/arm/mach-msm/include/mach/msm_iomap-copper.h \
    $(wildcard include/config/debug/msmcopper/uart.h) \
  arch/arm/mach-msm/include/mach/gpiomux.h \
    $(wildcard include/config/msm/gpiomux.h) \
  include/linux/errno.h \
  /home/arrrghhh/trees/kernel/asa-14/arch/arm/include/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \

arch/arm/mach-msm/gpiomux-v2.o: $(deps_arch/arm/mach-msm/gpiomux-v2.o)

$(deps_arch/arm/mach-msm/gpiomux-v2.o):
