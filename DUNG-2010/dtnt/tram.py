n = int(input())
a = list(map(int, input().split()))

a.sort()

res = float('inf')
for i in range(1, n):
    res = min(res, a[i] - a[i-1])

print(res)
