import sys, os, datetime

f = open("../.git/logs/refs/heads/master", "r")

lines = list(f.readlines())

while len(lines[-1]) <= 10:
    lines.pop()
line = lines[-1].split()

commit = line[1]
stamp = line[4]

print(f"{datetime.datetime.fromtimestamp(int(stamp)).strftime('%h %d, %Y')} \\texttt{{({commit[:6]}: {' '.join(line[7:])})}}")