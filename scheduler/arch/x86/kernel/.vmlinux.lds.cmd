cmd_arch/x86/kernel/vmlinux.lds := gcc -m32 -E -Wp,-MD,arch/x86/kernel/.vmlinux.lds.d  -nostdinc -isystem /usr/lib/gcc/i486-linux-gnu/4.2.4/include -D__KERNEL__ -Iinclude  -include include/linux/autoconf.h   -P -C -Ui386 -Ui386 -D__ASSEMBLY__ -o arch/x86/kernel/vmlinux.lds arch/x86/kernel/vmlinux.lds.S

deps_arch/x86/kernel/vmlinux.lds := \
  arch/x86/kernel/vmlinux.lds.S \
    $(wildcard include/config/x86/32.h) \
  arch/x86/kernel/vmlinux_32.lds.S \
    $(wildcard include/config/blk/dev/initrd.h) \
  include/asm-generic/vmlinux.lds.h \
  include/asm/thread_info.h \
  include/asm/thread_info_32.h \
    $(wildcard include/config/4kstacks.h) \
    $(wildcard include/config/debug/stack/usage.h) \
  include/linux/compiler.h \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/asm/page.h \
  include/asm/page_32.h \
    $(wildcard include/config/x86/use/3dnow.h) \
    $(wildcard include/config/x86/pae.h) \
    $(wildcard include/config/paravirt.h) \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/highmem4g.h) \
    $(wildcard include/config/highmem64g.h) \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/flatmem.h) \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/out/of/line/pfn/to/page.h) \
  include/asm-generic/page.h \
  include/asm/asm-offsets.h \
  include/asm/cache.h \
    $(wildcard include/config/x86/l1/cache/shift.h) \
    $(wildcard include/config/x86/vsmp.h) \
    $(wildcard include/config/smp.h) \
  include/asm/boot.h \
    $(wildcard include/config/physical/start.h) \
    $(wildcard include/config/physical/align.h) \

arch/x86/kernel/vmlinux.lds: $(deps_arch/x86/kernel/vmlinux.lds)

$(deps_arch/x86/kernel/vmlinux.lds):
