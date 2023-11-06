def penta(k):
  return k*(3*k-1)//2
def compute_partition(goal):
  p = [1]
  for n in range(1,goal+1):
    p.append(0)
    for k in range(1,n+1):
      c = (-1)**(k+1)
      for t in [penta(k), penta(-k)]:
        if (n-t) >= 0:
          p[n] = p[n] + c*p[n-t]
  return p
