
import sys
import math
import bisect
from sys import stdin,stdout
from math import gcd,floor,sqrt,log
from collections import defaultdict as dd
from bisect import bisect_left as bl,bisect_right as br
sys.setrecursionlimit(100000000)
inp    =lambda: int(input())
strng  =lambda: input().strip()
jn     =lambda x,l: x.join(map(str,l))
strl   =lambda: list(input().strip())
mul    =lambda: map(int,input().strip().split())
mulf   =lambda: map(float,input().strip().split())
seq    =lambda: list(map(int,input().strip().split()))
ceil   =lambda x: int(x) if(x==int(x)) else int(x)+1
ceildiv=lambda x,d: x//d if(x%d==0) else x//d+1
flush  =lambda: stdout.flush()
stdstr =lambda: stdin.readline()
stdint =lambda: int(stdin.readline())
stdpr  =lambda x: stdout.write(str(x))


mod = 1e9+7
N = 1e5


t = inp()

for _ in range(t):
    n  = inp()
    a = mul()
    lower = 0
    test = -1
    for i in range(n):
        if a[i] == 1:
            if i == 0:
                lower = 1
            elif i!= n-1:
                lower =2
                test = i
    fans = None
    if lower == 1:
        q = inp()
        for query in range(q):
            r  = inp()
            ans = None
            if r%n == 0:
                ans = (r//n)%mod
            else:
                if r%n == 1 and r > n:
                    ans = (r//n)%mod
                else:
                    ans = (r//(n+1))%mod
        fans = ans

    if lower == 2:
        sum = 0
        a = [0 for in range(N)]
        for i in range(n-1):
            if i == (test-1):
                sum += (arr[i]) - (arr[i]%2 == 0)
            else:
                sum += (arr[i]) - (arr[i]%2 == 1)
            
            a[i] = sum




401344249
443277519
987771259
749118108
28887561
35038307
646008062
344563932
766427162
547349409
748012539
586431448
540877869
654559531
685615034
561958823
523603871
176964305
777344170
896549895
359121267
595543775
455034547
792287918
432551653
157961911
770146254
336728130
312155697
775657345
583549505
20291997
481929108
906050383
696852759
81614147
418246522
759236555
694180014
327193130
662209549
446123854
921894956
50157299
122113553
617454041
670934565
543464770
514330113
991582429
29990017
752763603
713910248
698659578
35845067
226904775
305912520
646007068
33905273
554046408
751720968
196862724
296429196
874582186
774106150
79767015
149877680
286878894
64217121
705869463
468107551
95581904
920821826
573490674
58204771
305525981
25430886
183076199
740374893
829524081
984719470
517060418
642029396
457824962
666789932
705595581
303701245
570289897
804887542
113472577
337898363
861999337
900867979
494185171
149039935
467036804
879968997
388966477
168944074
736880045
836429407
890289983
225553278
700216474
179008087
402673157
867881237
945848537
260045558
336429443
200498930
629168431
963778715
363917283
660667268
268215897
168841174
348834871
252028133
839810117
146669726
405562653
294175848
722084120
845777928
434651551
211937848
845808375
328184984
109847516
428275569
349624045
114416573
811899561
254607774
84401155
360136429
11138895
137616486
893179604
358153338
269294278
619401900
479258446
11208131
172048440
508376192
149335056
9248359
447718496
344377343
393319189
261693252
133642707
339402774
426555190
269384072
583401651
643273456
41800052
           