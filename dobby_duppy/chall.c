#include <seccomp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <unistd.h>
#include <fcntl.h>

void init() {
  setvbuf(stdin, 0, 2, 0);
  setvbuf(stdout, 0, 2, 0);
}

void sandbox() {
  scmp_filter_ctx ctx;
  ctx = seccomp_init(SCMP_ACT_KILL);
  if (ctx == NULL) {
    exit(0);
  }
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(open),0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read),0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write),0);
  seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(dup2), 0);
}

int main()
{
  int fd; // [rsp+24h] [rbp-1Ch]
  void (*fcn)(void); // [rsp+28h] [rbp-18h]
  char buf[0x100]={0,};
	fcn=buf;

  init();
  sandbox();
  printf("Say hello to Dobby...if he is Dobby :) ");
  read(0, buf, 0x100uLL);
  puts("\nWhat? I'm Duppy! NOT Dobby!");
  puts("\nNow you are bliiiiiiiiind");

  fd = open("/dev/null", 2);

// stdin,stdout,stderr이 가리키는 파일을 /dev/null로 옮김
  dup2(fd, 0);
  dup2(fd, 1);
  dup2(fd, 2); 
                  
  fcn();
  return 0;
}
