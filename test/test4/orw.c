#include <fcntl.h>
#include <sys/sendfile.h>
#include <seccomp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>
#include <unistd.h>

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

int main(){
  char buf[0x20]={0,};
  read(0,buf,1);
  int fd=openat(AT_FDCWD,"./flag",O_RDONLY);
  sendfile(1,fd,0,0x20);
}
