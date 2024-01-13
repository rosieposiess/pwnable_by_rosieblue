// Compile: gcc -fno-stack-protector -z noexecstack -no-pie -Wl,-z,relro,-z,now test.c -o test

#include <fcntl.h>
#include <sys/sendfile.h>
#include <seccomp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>
#include <unistd.h>

void init() {
  setvbuf(stdin, 0, 2, 0);
  setvbuf(stdout, 0, 2, 0);
}

void sandbox() {
  scmp_filter_ctx ctx;
  ctx = seccomp_init(SCMP_ACT_ALLOW);
  if (ctx == NULL) {
    exit(0);
  }
  seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(fork),0);
  seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(clone),0);
  seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(vfork),0);
  seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(execveat), 0);
  seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(execve), 0);
  seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(open_by_handle_at),0);
  seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(open), 0);
  seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(write),0);
  seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(writev),0);
  seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(pwritev),0);
  seccomp_load(ctx);
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
