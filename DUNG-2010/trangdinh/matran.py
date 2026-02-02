n = int(input())
nlist = []
res = 0
for i in range(n):
    nlist.append((list(map(int,input().split()))))
for i in range(n):
    res = max(res,sum(nlist[i]))
print(res)