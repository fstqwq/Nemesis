import math
import sys
def inp():
	while True:
		_INPUT = input().split() # sys.stdin.read().split()
		for j in _INPUT:
			yield j
read = inp().__next__
a = []
def solve(l, r):
	if l + 1 >= r:
		return 2 ** 64
	m = (l + r) // 2
	mx = a[m][0]
	v = []
	ret = min(solve(l, m), solve(m, r))
	for i in range(l, r):
		if (a[i][0] - mx) ** 2 < ret:
			v.append(a[i])
	v.sort(key=lambda x : x[1])
	for i in range(len(v)):
		for j in range(i + 1, len(v)):
			if (v[i][1] - v[j][1]) ** 2 > ret:
				break
			ret = min(ret, (v[i][0] - v[j][0]) ** 2 + (v[i][1] - v[j][1]) ** 2)
	return ret

n = int(read())
for i in range(n):
	x = int(read())
	y = int(read())
	a.append((x, y))
a.sort(key=lambda x : x[0])
print("%.4f" % math.sqrt(solve(0, n)))
