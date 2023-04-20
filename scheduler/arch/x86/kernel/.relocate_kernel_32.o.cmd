cmd_arch/x86/kernel/relocate_kernel_32.o := gcc -m32 -Wp,-MD,arch/x86/kernel/.relocate_kernel_32.o.d  -nostdinc -isystem /usr/lib/gcc/i486-linux-gnu/4.2.4/include -D__KERNEL__ -Iinclude  -include include/linux/autoconf.h -D__ASSEMBLY__   -Iinclude/asm-x86/mach-default -gdwarf-2     -c -o arch/x86/kernel/relocate_kernel_32.o arch/x86/kernel/relocate_kernel_32.S

deps_arch/x86/kernel/relocate_kernel_32.o := \
  arch/x86/kernel/relocate_kernel_32.S \
    $(wildcard include/config/x86/pae.h) \
  include/linux/linkage.h \
  include/asm/linkage.h \
    $(wildcard include/config/x86/32.h) \
  include/asm/linkage_32.h \
    $(wildcard include/config/x86/alignment/16.h) \
  include/asm/page.h \
  include/asm/page_32.h \
    $(wildcard include/config/x86/use/3dnow.h) \
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
  include/asm/kexec.h \
  include/asm/kexec_32.h \

arch/x86/kernel/relocate_kernel_32.o: $(deps_arch/x86/kernel/relocate_kernel_32.o)

$(deps_arch/x86/kernel/relocate_kernel_32.o):
