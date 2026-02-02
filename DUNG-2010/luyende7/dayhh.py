n,k = map(int,input().split())
a = list(map(int,input().split()))
res = 0
for i in range(n):
    for j in range(i+1,n+1):
        if sum(a[i:j]) >= k:
             res = max(res,(sum(a[i:j])//len(a[i:j])))
print(res)