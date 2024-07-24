import sys

BASE = [2,325,9375,28178,450775,9780504,1795265022]

def check(M, base):
	a = M - 1
	while not a & 1:
		a >>= 1
	w = pow(base, a, M)
	for _ in range(a, M - 1, a):
		if w == 1 or w == M - 1:
			return True
		w = pow(w, 2, M)
	return False

def isprime(a):
	if a < 4:
		return a > 1
	if not a & 1:
		return False
	for base in BASE:
		if not check(a, base):
			return False
	return True

import random,datetime,time

if len(sys.argv) < 2:
	print("Usage: python script.py <n> [seed]")
	sys.exit(1)

Range = map(float, sys.argv[1:])
# [500, 1e3, 3e4, 1e5, 1e6, 5e6, 1e7, 2e7, 1e9, 2e9, 1e13, 0.9e18, 1e18]
print("{\\textbf{Random primes} generated at ", time.asctime( time.localtime(time.time()) ), "\\\\")
for lim in Range:
	print(("\\textbf{%0.0e} " % lim).replace("+0", "").replace("+", ""), end="")
	lim = int(lim)
	lower = int(lim * 0.93) - 100
	upper = int(lim * 1.07) + 100
	cur = set ()
	dead = 0
	s = ""
	while True:
		if upper - lower > 1e10:
			if random.randint(0, 1) == 0:
				x = str(lim - random.randint(1, 100000))
			else:
				x = str(lim + random.randint(1, 100000))
			l = len(x) - 2 - 5
			x = x[:2] + ("1234"* 100)[:l] + x[2+l:]
			x = int(x)
		else:
			x = random.randint(lower, upper)
		if isprime(x) and x not in cur:
			s += " " + str(x)
			if len(s) > 62:
				break
			cur.add(x)
		else:
			dead += 1
			if dead > 500:
				break
	cur = sorted(cur)
	for i in cur:
		print(i, end=" ")
	print("\\\\")
print("}")