def IO_and_Exceptions():
    try:
        with open("a.in", mode="r") as fin:
            for line in fin:
                a = list(map(int, line.split()))
                print(a, end = "\n")
    except:
        exit()
    assert False, '17 cards can\'t kill me'
def Random():
    import random as rand
    rand.randint(0, 10)
    rand.random(), rand.normalvariate(0.5, 0.1)
    ### Operating list
    l = [str(i) for i in range(9)]
    sorted(l), min(l), max(l), len(l)
    l.append(99),l.index(99),l.insert(0, 1),l.pop(0)
    rand.shuffle(l)
    rand.choice(l), rand.sample(l, 3) # Index Err
    l.sort(key=lambda x:x ^ 1,reverse=True)
    import functools as ft
    l.sort(key=ft.cmp_to_key(lambda x, y:(y^1)-(x^1)))
def Sample_Interaction():
    # find perm of 6 num in 4 qrys
    a = [4, 8, 15, 16, 23, 42]
    def qry(x, y):
        print("? {:d} {:d}".format(x + 1, y + 1))
        g[x][y] = int(input()) # no need flush 
        g[y][x] = g[x][y]
    import itertools
    g = [[-1 for i in range(6)] for j in range(6)]
    for i in range(4): qry(i, i + 1)
    for p in list(itertools.permutations(a, 6)):
        ans = 1
        for i in range(4):
            if p[i] * p[i + 1] != g[i][i + 1]:
                ans = 0
        if ans:
            print("! ", end="")
            for i in range(6):
                print(p[i], end = " ")
            print("")
def FractionOperation():
    from fractions import Fraction 
    a = Fraction(0.233).limit_denominator()
    a == Fraction("0.233") #True
    a.numerator, a.denominator, str(a)
def DecimalOperation():
    import decimal
    from decimal import Decimal, getcontext
    getcontext().prec = 100
    getcontext().rounding = getattr(decimal, 'ROUND_HALF_EVEN')
    # default; other: FLOOR, CELILING, DOWN, ...
    getcontext().traps[decimal.FloatOperation] = True
    Decimal((0, (1, 4, 1, 4), -3)) # 1.414
    a = Decimal(1<<31) / Decimal(100000)
    print(round(a, 5)) # total digits
    print(a.quantize(Decimal("0.00000")))
    # 21474.83648
    print(a.sqrt(), a.ln(), a.log10(), a.exp())
    print(a % Decimal("0.01"), a // Decimal("0.01"))
    print(a ** 2, a.shift(2))
def Complex():
    a = 1-2j
    print(a.real, a.imag, a.conjugate())
def Using_Class():
    '''
    Operators satisfy __*__, __r*__, __i*__.
    add sub mul truediv floordiv mod divmod pow
    and or xor lshift rshift
    eq ne gt lt le
    Following is a sample:
    '''
    class Frac:
        x, y = 0, 0
        def __init__(self, a = 0, b = 1):
            self.x = a
            self.y = b
        def __add__(self, oth):
            ret = Frac()
            ret.x = self.x * oth.y + self.y * oth.x
            ret.y = self.y * oth.y
            return ret

