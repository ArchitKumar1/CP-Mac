from random import *

M = 100000
N = 100000
D = 5
import sys
file = open('ddmistinput.txt', 'a')
sys.stdout = file
print("")
print(N,D)
for i in range(N):
    for j in range(D):
        print(randint(1,M))



file.close()