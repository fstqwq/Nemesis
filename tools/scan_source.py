# scan all code, in order to find 'dead code':
# 1. unmodified since very long
# 2. not included

import os, sys, datetime
import subprocess

working_path = "../src/src/"
texs = ["../src/main.tex", "../src/src/TreeandGraph/图论知识.tex"]
log_file = "scan.log"

main_text = ""
for tex in texs:
    with open(tex, 'r') as f:
        main_text += f.read()

def check_status(filename):
    p = main_text.find(filename)
    if p == -1:
        return "Not included"
    while p >= 0 and main_text[p] != '\n':
        if main_text[p] == '%':
            return "Commented   "
        p -= 1
    return "OK          "


time_name = []

for (dirpath, dirnames, filenames) in os.walk(working_path):
    for fname in filenames:
        rfname = dirpath + '/' + fname
        batcmd = r'git log -1 --format=%ct "' + rfname + '"'
        result = int(subprocess.check_output(batcmd, shell=True))
        print(datetime.datetime.fromtimestamp(result).strftime('%y%m%d %H:%M'), rfname)
        time_name.append((result, rfname[len(working_path):]))

time_name.sort()

output = open(log_file, "w")
for i in time_name:
    print(datetime.datetime.fromtimestamp(i[0]).strftime('%y%m%d %H:%M'), check_status(i[1]), i[1], file=output)
output.close()

print("Write log to file ", log_file)