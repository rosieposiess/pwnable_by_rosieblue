// Compile: gcc -fno-stack-protector -z noexecstack -no-pie -Wl,-z,relro,-z,now test.c -o test

#include <fcntl.h>
#include <linux/audit.h>
#include <linux/filter.h>
#include <linux/seccomp.h>
#include <linux/unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/prctl.h>
#include <unistd.h>

#define ALLOW_SYSCALL(name)                               \
  BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, __NR_##name, 0, 1), \
      BPF_STMT(BPF_RET + BPF_K, SECCOMP_RET_ALLOW)
#define KILL_PROCESS BPF_STMT(BPF_RET + BPF_K, SECCOMP_RET_KILL)
#define syscall_nr (offsetof(struct seccomp_data, nr))
#define arch_nr (offsetof(struct seccomp_data, arch))
/* architecture x86_64 */
#define ARCH_NR AUDIT_ARCH_X86_64

void init() {
  setvbuf(stdin, 0, 2, 0);
  setvbuf(stdout, 0, 2, 0);
}

int sandbox() {
struct sock_filter filter[] = {
      /* Validate architecture. */
      BPF_STMT(BPF_LD + BPF_W + BPF_ABS, arch_nr),
      BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, ARCH_NR, 1, 0),
      BPF_STMT(BPF_RET + BPF_K, SECCOMP_RET_KILL),
      /* Get system call number. */
      BPF_STMT(BPF_LD + BPF_W + BPF_ABS, syscall_nr),
      /* List allowed syscalls. */
      ALLOW_SYSCALL(read),
      ALLOW_SYSCALL(rt_sigreturn),
      KILL_PROCESS,
  };

  struct sock_fprog prog = {
      .len = (unsigned short)(sizeof(filter) / sizeof(filter[0])),
      .filter = filter,
  };
  if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) == -1) {
    perror("prctl(PR_SET_NO_NEW_PRIVS)\n");
    return -1;
  }
  if (prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog) == -1) {
    perror("Seccomp filter error\n");
    return -1;
  }
  return 0;
}

void main() {
  init();
  sandbox();

  asm(".intel_syntax noprefix");
  asm("mov    QWORD PTR [rbp-0x10],0x0;\
       mov    QWORD PTR [rbp-0x8],0x0;\
       lea    rax,[rbp-0x10];\
       mov    rsi,rax;\
       mov    rax,QWORD PTR [rbp-0x8];\
       mov    edx,0x300;\
       mov    edi,eax;\
       syscall");
}
