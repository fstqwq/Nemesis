def fib(n): # 返回 F(n) 和 F(n + 1)
    if not n: return (0, 1)
    a, b = fib(n >> 1)
    c, d = a * (2 * b - a), a * a + b * b
    return (d, c + d) if n & 1 else (c, d)