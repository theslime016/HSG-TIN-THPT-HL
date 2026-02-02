import math

res = 0
n = int(input())
a = list(map(int, input().split()))

for i in range(n):
    for j in range(i + 1, n):
        res = max(res, math.gcd(a[i], a[j]))

print(res)
