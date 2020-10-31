from random import *
import sys

file = open('input.txt', 'w')
sys.stdout = file

N = 200
Q = 200


print(N)
for i in range(N):
    print(randint(1,1e9),end= " ")

print(Q)
for i in range(Q):
    L = randint(1,N)
    R = randint(L,N)
    print(L,R)

file.close()