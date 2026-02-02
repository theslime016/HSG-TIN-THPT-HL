n,m = map(int,input().split())
a = list(map(int,input().split()))
for i in range(m):
    a = a[1:]+a[:1]
print(a)