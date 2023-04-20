cmd_arch/x86/kernel/entry_32.o := gcc -m32 -Wp,-MD,arch/x86/kernel/.entry_32.o.d  -nostdinc -isystem /usr/lib/gcc/i486-linux-gnu/4.2.4/include -D__KERNEL__ -Iinclude  -include include/linux/autoconf.h -D__ASSEMBLY__   -Iinclude/asm-x86/mach-default -gdwarf-2     -c -o arch/x86/kernel/entry_32.o arch/x86/kernel/entry_32.S

deps_arch/x86/kernel/entry_32.o := \
  arch/x86/kernel/entry_32.S \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/vm86.h) \
    $(wildcard include/config/paravirt.h) \
    $(wildcard include/config/x86/mce.h) \
    $(wildcard include/config/xen.h) \
  include/linux/linkage.h \
  include/asm/linkage.h \
    $(wildcard include/config/x86/32.h) \
  include/asm/linkage_32.h \
    $(wildcard include/config/x86/alignment/16.h) \
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
  include/asm/irqflags.h \
  include/asm/irqflags_32.h \
    $(wildcard include/config/debug/lock/alloc.h) \
  include/asm/processor-flags.h \
  include/asm/paravirt.h \
    $(wildcard include/config/x86/local/apic.h) \
    $(wildcard include/config/highpte.h) \
    $(wildcard include/config/smp.h) \
  include/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \
  include/asm/segment.h \
  include/asm/segment_32.h \
  include/asm/smp.h \
  include/asm/smp_32.h \
    $(wildcard include/config/x86/io/apic.h) \
    $(wildcard include/config/hotplug/cpu.h) \
  include/asm/desc.h \
  include/asm/desc_32.h \
  include/asm/ldt.h \
  include/asm/percpu.h \
  include/asm/percpu_32.h \
  include/asm/dwarf2.h \
  include/asm/dwarf2_32.h \
    $(wildcard include/config/unwind/info.h) \
    $(wildcard include/config/as/cfi/signal/frame.h) \
  include/asm-x86/mach-default/irq_vectors.h \
  include/asm-x86/mach-default/irq_vectors_limits.h \
  include/asm-x86/mach-default/entry_arch.h \
    $(wildcard include/config/x86/smp.h) \
    $(wildcard include/config/x86/mce/p4thermal.h) \
  arch/x86/kernel/syscall_table_32.S \

arch/x86/kernel/entry_32.o: $(deps_arch/x86/kernel/entry_32.o)

$(deps_arch/x86/kernel/entry_32.o):
