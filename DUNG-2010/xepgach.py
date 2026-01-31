n,m = map(int,input().split())
a = []
req = 0
cnt = 0
for i in range(n):
    b = list(map(int,input().split()))
    req = max(req,max(b))
    a.append(b)

for i in range(n):
    for j in range(m):
        if a[i][j] < req:
            cnt +=  (req - a[i][j])
print(cnt)