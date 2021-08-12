def isprime(x):
	if x <= 3:
		return x >= 2
	for i in range(2, x):
		if x % i == 0:
			return False
		if i * i > x:
			break
	return True

import random
T = 10
Range = [1e3, 1e5, 1e6, 1e7, 1e9]
print("\\begin{itemize}")
for lim in Range:
	print(("\\item[%0.0e] " % lim).replace("+0", ""), end="")
	lower = int(lim * 0.9)
	upper = int(lim * 1.1)
	cur = set ()
	while len(cur) < T:
		x = random.randint(lower, upper)
		if isprime(x):
			cur.add(x)
	cur = sorted(cur)
	for i in cur:
		print(i, end=" ")
	print()
print("\\end{itemize}")