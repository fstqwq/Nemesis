def build(a, b, c, d, level = 1):
    x = a + c; y = b + d
    build(a, b, x, y, level + 1)
    build(x, y, c, d, level + 1)
build(0, 1, 1, 0) # 最简分数, Stern-Brocot
build(0, 1, 1, 1) # 最简真分数, Farey