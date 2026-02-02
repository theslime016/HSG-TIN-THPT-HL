n = int(input())
nlist = list(map(int, input().split()))

a = sorted(nlist)
d = []

print(*a)

for i in range(min(5, len(a))):
    max_cost = a[i] * 20
    if n >= max_cost:
        n -= max_cost
        d.append(20)
    else:
        c = n // a[i]
        d.append(c)
        n -= c * a[i]

print(d)
print(n)   # n còn lại
