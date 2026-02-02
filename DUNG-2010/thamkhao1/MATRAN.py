n,m = map(int,input().split())
a = []

for i in range(n):
    b = list(map(int,input().split()))
    a.append(max(b))
a = sorted(a,reverse=True)
print(a[0],a[1])