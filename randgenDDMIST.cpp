from random import *

M = 100000
N = 2000
D = 5
print(N,D,file = f)

f = open("ddinput.txt", "a")

for i in range(N):
    for j in range(D):
        print(randint(1,M),end = " ")
    print("",file = f)

f.close()