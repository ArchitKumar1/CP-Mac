from random import *
import sys

file = open('input.txt', 'w')
sys.stdout = file

T = 4
MAXN = 1e3
MAXA = 1e4
MAXR = 1e12

Q = 40
print(T)
for _ in range(T):
    N = randint(1,MAXN)
    print(N)
    for i in range(N):
        print(randint(1,MAXA),end= " ")
    print("")
    print(Q)
    for i in range(Q):
        print(randint(1,MAXR),end= " ")
    print("")
file.close()