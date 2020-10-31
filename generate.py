from random import *
import sys

file = open('input.txt', 'w')
sys.stdout = file

N = 50000

MAXN = 50000

print(1)
print(N)
for i in range(N):
    print(randint(1,MAXN),end= " ")

file.close()