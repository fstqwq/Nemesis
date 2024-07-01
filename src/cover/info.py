import sys, os, datetime, subprocess

result = subprocess.run(["git", "log", "-n", "1"], stdout=subprocess.PIPE)

lines = result.stdout.splitlines()

date_str = lines[2].decode()
date_format = "Date:   %a %b %d %H:%M:%S %Y %z"
stamp = datetime.datetime.strptime(date_str, date_format).timestamp()

commit = lines[0].decode().split()[1]
info = lines[4].decode().strip().replace('_', '\\_')

print(f"{datetime.datetime.fromtimestamp(int(stamp)).strftime('%h %d, %Y')} ({commit[:6]}: {info})"
	.replace("&", "\\&")
	.replace("%", "\\%")
	.replace("#", "\\#")) # LaTeX escape
