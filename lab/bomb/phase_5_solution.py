s1 = "flyers"
s2 = "maduiersnfotvbyl"
print("".join(list(chr(s2.index(c) + 0b1100000) for c in s1)))
print("".join(list(chr(s2.index(c) + 0b1000000) for c in s1)))