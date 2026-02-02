n = int(input())
nlist = list(map(int, input().split()))
res = 0
for i in range(n):
    if nlist[i] % 3 == 0:
        res += nlist[i]

print(res)