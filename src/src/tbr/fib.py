def fib(n): # F(n), F(n + 1)
    if not n: return (0, 1)
    a, b = fib(n >> 1)
    c = a * (2 * b - a)
    d = a * a + b * b
    if n & 1:
        return (d, c + d)
    else:
        return (c, d)