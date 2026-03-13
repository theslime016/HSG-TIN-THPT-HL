n = input()
import re
def prm(n):
    snt = [True] *(n+1)
    snt[0] = snt[1] = False
    for i in range(2,int(n**0.5)+1):
        if snt[i]:
            for j in range(i*i,n+1,i):
                snt[j] = False
    return snt
snt = prm(1000000)
a = re.findall(r'\d+',n)
print   (sum(1 for i in a if snt[int(i)] == True) )
