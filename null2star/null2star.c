// gcc -o test test.c -fno-stack-protector -Wl,-z,relro,-z,now -fPIC -pie -fPIE -pie

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

char buf[80]; //전역변수

void alarm_handler()
{
    puts("TIME OUT");
    exit(-1);
}

void initialize()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    signal(SIGALRM, alarm_handler);
    alarm(60);
}

int null2star(char * s1, const char * s2) {
    int result=strcmp(s1, s2);
    if (!result) {        
         s1[strlen(s1)] = '*'; //s1의 null을 *로 바꿈
         }     
    return result;
}


void print_addr(char* buf){ //이 함수로 스택의 리턴 어드레스 구하기
		signed long* addr=0;
    off_t off1=0;
    off_t off2=0;
    
    read(0,&addr,8); //stdin주소
    read(0,&off1,2);
    read(0,&off2,2);
    
    if(*(void*)(addr+off1)==*(void*)(buf+off2)) {
    	//addr:stdin을, off1: 0x40, off2:0x218 을 넣으면 만족할듯 
    	printf("Wanted Address: %p\n",(void*)(buf+off2));
    }
}


void read_command(char *s)
{
    int len;
    len = read(0, s, 512); //512만큼 읽어서 s에 저장. len은 읽은 바이트 수 
    if (s[len - 1] == '\x0a') //맨마지막 원소가 \n(엔터)인 경우 \0으로 바꾸기
        s[len - 1] = '\0';}

int main(int argc, char *argv[])
{
    long long dummy = 0;
    char command[512];
    long *src = 0;
    memset(command, 0, sizeof(command) - 1); //511byte만큼 command를 0으로 채우기
	
    initialize();
    printf("stdout: %p\n", stdout); //라이브러리 릭 가능

    while (1)
    {
        printf("Your Command: ");
        read_command(command); //command에 최대 512byte만큼 저장

        if (!null2star(command, "read"))
        {
            fgets(buf, sizeof(buf) - 1, stdin);
        }   
                
       	else if (!null2star(command, "print"))
				{
       		print_addr(command);
      	}
        
        else if (!null2star(command, "write")) //strncmp에서 strcmp로 바꿈 -> printf₩00₩x20해줘야할듯
        {
            if (strtok(command, " ")) //command를 " "(0x20)으로 나눈 첫번째 덩어리의 포인터
            {
                src = (long*) strtok(NULL, " "); //두번째 덩어리 가리키는 포인터가 src
                if (src)
                    memcpy(stdin, src, 0x48); 
            }
        }
        
        else if (!null2star(command, "exit"))
        {
            return 0;
        }

        else
        {
            printf("%s: command not found\n", command);
        }
        
        memset(command, 0, sizeof(command) - 1);
    }
    return 0;
}
