# pwnable_by_rosieblue
Self-made pwnable challenges

Challenge | keyword|
---|---|
Santa House| `Address Leak`|
sandrop|`SROP`,`SECCOMP`|
u_can_read|`SROP`,`SECCOMP`|
dobby_duppy|`Shellcode`,`dup2`|

<br/>

## 1. Santa House
> In this challenge, you have to leak `PIE` and `Library Base` using encrypted random values. After leaking addresses `shell` can be obtained using techniques such as `Stack Pivoting`.
* Challenge of [2023 Dreamhack X-MAS CTF](https://dreamhack.io/ctf/426) (Final solver team 13 out of 600)
* Currently ported to [Dreamhack](https://dreamhack.io/wargame/challenges/1071)

<br/>


## 2. sandrop
> Bypassing `SECCOMP` Filter by configuring `SROP chain`
* This challenge is presented at [EWHA 1st ESC CTF](https://ecs.ctfd.io/) to be held in February 2024

<br/>


## 3. u_can_read
> Bypassing `SECCOMP` Filter by configuring `SROP chain`
* Easy version of `sandrop` challenge above
* This challenge is presented at [EWHA 1st ESC CTF](https://ecs.ctfd.io/) to be held in February 2024

<br/>


## 4. dobby_duppy
> Bypassing 'dup2' function with shellcode
* This challenge is presented at [EWHA 1st ESC CTF](https://ecs.ctfd.io/) to be held in February 2024
* Currently ported to [Dreamhack](https://dreamhack.io/wargame/challenges/1110)


