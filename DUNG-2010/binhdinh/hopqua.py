n,m = map(int,input().split())
a = list(map(int,input().split()))
b = list(map(int,input().split()))
a.sort()
b.sort()

total = 0
tota = 0
totb = 0
possible = True

while totb < m:
    while tota < n and a[tota] < b[totb]:
        tota +=1
    if tota == n:
        possible = False
        break
    total += a[tota]
    tota +=1
    totb +=1
if possible:
    print(total)
else:
    print(-1)