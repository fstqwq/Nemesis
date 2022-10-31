def isprime(x):
	if x <= 3:
		return x >= 2
	if x % 2 == 0:
		return False
	for i in range(3, x, 2):
		if x % i == 0:
			return False
		if i * i > x:
			break
	return True

import random,datetime,time

Range = [1e3, 1e5, 3e5, 5e5, 1e6, 2e6, 5e6, 1e7, 2e7, 1e9]
print("{\\textbf{Random primes} generated at ", time.asctime( time.localtime(time.time()) ), "\\\\")
for lim in Range:
	print(("\\textbf{%0.0e} " % lim).replace("+0", ""), end="")
	lower = int(lim * 0.94)
	upper = int(lim * 1.07)
	cur = set ()
	dead = 0
	s = ""
	while True:
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