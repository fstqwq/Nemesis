import sys, os

f = open("../.git/refs/heads/master", "r")

print(f.read()[:7])