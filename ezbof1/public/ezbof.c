#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void vul(){
        system("/bin/sh");
}

int main(){

        setvbuf(stdin, 0, _IONBF, 0);
        setvbuf(stdout, 0, _IONBF, 0);

        char buf[8]={0,};
        read(0,buf,0x10);

        printf("Your data:%s\n",buf);
        printf("Good bye msg?");

        scanf("%s",buf);

        return 0;
}

