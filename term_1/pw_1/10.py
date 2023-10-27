a = 5
b = float(input("b = "))
c = 5
d = int(input("d = "))
a = a + b - 2
c = c + 1
d = c - a + d
a = a * c
c = c - 1
a = a / 10
c = c / 2
b = b - 1
d = d * (c + b + a)
print(f"a = {a} b = {b} c = {c} d = {d}")
