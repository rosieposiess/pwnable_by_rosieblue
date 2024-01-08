//gcc -o chall chall.c -Wl,-z,relro,-z,now -fno-stack-protector

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>


void secret_gift() {
   const char* secret_gift="Secret Gift for you";
   system(secret_gift);
}

void initialize()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
}

void weird_message(void *addr, int len)
{
    int fd = open("./flag", O_WRONLY); 
    read(fd, addr, len); //wronly로 바꿔서 에러유발
    *(long*)addr ^= ((*(long*)addr) << 12);
}

void give_present(char* name){
    char dummy[0x10]={};
    char gift[0x10]={};
    printf("Santa will give you a present. Wait a second..\n");
    strcpy(gift,name);
    weird_message(&gift,6);
    if (strlen(gift)>8){
        weird_message(gift+8,6);
                        }
    printf("🎅:Here is your present %s!\n",gift);
}

int main()
{
    initialize();    
    char goodbye_msg[0x20]={};
    long len;
    char name[0x10];
    char hello_msg[8]; 

    //풀이자는 스택주소를 알 수 있음 (참고로 aslr때문에 계속 바뀜)
    printf("This is your invitation key %u. Now you can go in!\n",hello_msg[0]&0xff);
    printf("🎄Welcome to Santa's House!🎄\n");
    printf("Say hello to Santa :)\n\n");
    printf("You: ");
    read(0,hello_msg,8);
    weird_message(&hello_msg, 6); 
    printf("🎅:%ld!\n\n",*(long*)hello_msg); 


    //pie base 주소 구함
    printf("Let me know your name: ");
    len=read(0,name,0x10);
    name[0xf]=0; //prevent memory leak 
    if (name[len-1] == '\n')
          name[len-1] = 0;
    give_present(name);

    //bof
    puts("\n💌Leave a good bye message to santa: ");
    read(0,goodbye_msg,0x40);

    return 0;
}
