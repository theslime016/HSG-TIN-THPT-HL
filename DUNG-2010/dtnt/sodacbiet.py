import math
snt = 0
scp  = 0
def prm(n):
    if n< 2:
        return False
    for i in range(2,math.isqrt(n)+1):
        if n % i == 0:
            return False
    return True

def la_so_chinh_phuong(n):
    if n < 0:
        return False
    return int(math.sqrt(n)) ** 2 == n

n = int(input())
a = list(map(int,input().split()))

for i in range(n):
    if prm(a[i]):
        snt +=1
    if la_so_chinh_phuong(a[i]):
        scp += a[i]

print(snt)
print(scp)