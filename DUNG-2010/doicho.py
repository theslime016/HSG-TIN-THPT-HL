n,m = map(int,input().split())
a = list(map(int,input().split()))
sw = []
for i in range(m):
    x1,y1 = map(int,input().split())
    sw.append((x1,y1))
for x,y in reversed(sw):
    a[x-1],a[y-1] = a[y-1],a[x-1]
print(*a)