cmd_arch/x86/kernel/vsyscall_32.lds := gcc -m32 -E -Wp,-MD,arch/x86/kernel/.vsyscall_32.lds.d  -nostdinc -isystem /usr/lib/gcc/i486-linux-gnu/4.2.4/include -D__KERNEL__ -Iinclude  -include include/linux/autoconf.h   -P -C -Ui386 -D__ASSEMBLY__ -o arch/x86/kernel/vsyscall_32.lds arch/x86/kernel/vsyscall_32.lds.S

deps_arch/x86/kernel/vsyscall_32.lds := \
  arch/x86/kernel/vsyscall_32.lds.S \
  include/asm/asm-offsets.h \

arch/x86/kernel/vsyscall_32.lds: $(deps_arch/x86/kernel/vsyscall_32.lds)

$(deps_arch/x86/kernel/vsyscall_32.lds):
