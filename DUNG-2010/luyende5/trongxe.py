from collections import Counter
n = int(input())
a = []
res = 0
for i in range(n):
    b = int(input())
    a.append(b)
s = Counter(a)
for i,v in s.items():
    if v <= 5:
        res +=100
        print(v)
    elif v > 5:
        res +=(100 + (v-5))
        print(v)
print(res)
