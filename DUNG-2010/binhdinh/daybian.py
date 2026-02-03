n,k = map(int,input().split())
a = list(map(int,input().split()))
res = []

for i in range(n+1):
    for j in range(i,n+1):
        if sum(a[i:j]) == k:
            res.append((a[i:j]))
print(len(res))
