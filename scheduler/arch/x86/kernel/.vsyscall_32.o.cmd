cmd_arch/x86/kernel/vsyscall_32.o := gcc -m32 -Wp,-MD,arch/x86/kernel/.vsyscall_32.o.d  -nostdinc -isystem /usr/lib/gcc/i486-linux-gnu/4.2.4/include -D__KERNEL__ -Iinclude  -include include/linux/autoconf.h -D__ASSEMBLY__   -Iinclude/asm-x86/mach-default -gdwarf-2     -c -o arch/x86/kernel/vsyscall_32.o arch/x86/kernel/vsyscall_32.S

deps_arch/x86/kernel/vsyscall_32.o := \
  arch/x86/kernel/vsyscall_32.S \
  include/linux/init.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/acpi/hotplug/memory.h) \
  include/linux/compiler.h \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \

arch/x86/kernel/vsyscall_32.o: $(deps_arch/x86/kernel/vsyscall_32.o)

$(deps_arch/x86/kernel/vsyscall_32.o):
