cmd_arch/x86/kernel/vsyscall-note_32.o := gcc -m32 -Wp,-MD,arch/x86/kernel/.vsyscall-note_32.o.d  -nostdinc -isystem /usr/lib/gcc/i486-linux-gnu/4.2.4/include -D__KERNEL__ -Iinclude  -include include/linux/autoconf.h -D__ASSEMBLY__   -Iinclude/asm-x86/mach-default -gdwarf-2     -c -o arch/x86/kernel/vsyscall-note_32.o arch/x86/kernel/vsyscall-note_32.S

deps_arch/x86/kernel/vsyscall-note_32.o := \
  arch/x86/kernel/vsyscall-note_32.S \
    $(wildcard include/config/xen.h) \
  include/linux/version.h \
  include/linux/elfnote.h \

arch/x86/kernel/vsyscall-note_32.o: $(deps_arch/x86/kernel/vsyscall-note_32.o)

$(deps_arch/x86/kernel/vsyscall-note_32.o):
