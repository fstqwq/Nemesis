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
Range = [1e3, 1e5, 5e5, 1e6, 2e6, 1e7, 1e9]
print("{")
print("\\begin{itemize}")
print(r"\setlength{\parindent}{0em}\setlength{\parskip}{0em}\renewcommand{\baselinestretch}{.5}")
for lim in Range:
	print(("\\item[%0.0e] " % lim).replace("+0", ""), end="")
	lower = int(lim * 0.96)
	upper = int(lim * 1.06)
	cur = set ()
	dead = 0
	while len(cur) < T:
		x = random.randint(lower, upper)
		if isprime(x) and x not in cur:
			cur.add(x)
		else:
			dead += 1
			if dead > 10000:
				break
	cur = sorted(cur)
	for i in cur:
		print(i, end=" ")
	print()
print("\\end{itemize}")
print("}")