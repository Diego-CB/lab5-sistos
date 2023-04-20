cmd_arch/x86/kernel/vsyscall-int80_32.o := gcc -m32 -Wp,-MD,arch/x86/kernel/.vsyscall-int80_32.o.d  -nostdinc -isystem /usr/lib/gcc/i486-linux-gnu/4.2.4/include -D__KERNEL__ -Iinclude  -include include/linux/autoconf.h -D__ASSEMBLY__   -Iinclude/asm-x86/mach-default -gdwarf-2     -c -o arch/x86/kernel/vsyscall-int80_32.o arch/x86/kernel/vsyscall-int80_32.S

deps_arch/x86/kernel/vsyscall-int80_32.o := \
  arch/x86/kernel/vsyscall-int80_32.S \
  arch/x86/kernel/vsyscall-sigreturn_32.S \
  include/asm/unistd.h \
    $(wildcard include/config/x86/32.h) \
  include/asm/unistd_32.h \
  include/asm/asm-offsets.h \

arch/x86/kernel/vsyscall-int80_32.o: $(deps_arch/x86/kernel/vsyscall-int80_32.o)

$(deps_arch/x86/kernel/vsyscall-int80_32.o):
