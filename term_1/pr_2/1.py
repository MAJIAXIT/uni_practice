def f(a, b):
    if a > 10:
        return a - b
    elif 0 < a <= 10 and b > 0:
        return (a - b) / (a + b)
    else:
        return b


print(f(-4, 10))
