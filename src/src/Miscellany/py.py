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
	rand.normalvariate(0.5, 0.1)
	l = [str(i) for i in range(9)]
	sorted(l), min(l), max(l), len(l)
	rand.shuffle(l)
	l.sort(key=lambda x:x ^ 1,reverse=True)
	import functools as ft
	l.sort(key=ft.cmp_to_key(lambda x, y:(y^1)-(x^1)))
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
	print(a.sqrt(), a.ln(), a.log10(), a.exp(), a ** 2)
def Complex():
	a = 1-2j
	print(a.real, a.imag, a.conjugate())
def FastIO():
	import atexit
	import io
	import sys
	_INPUT_LINES = sys.stdin.read().splitlines()
	input = iter(_INPUT_LINES).__next__
	_OUTPUT_BUFFER = io.StringIO()
	sys.stdout = _OUTPUT_BUFFER
	@atexit.register
	def write():
		sys.__stdout__.write(_OUTPUT_BUFFER.getvalue())
