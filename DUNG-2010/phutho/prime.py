n = input()
length = len(n)
res = []
ans = 0
for mask in range(1, 1 << length):

    if mask == (1 << length) - 1:
        continue

    s = ""
    for i in range(length):
        if mask & (1 << i):
            s += n[i]

    if s:
        res.append(int(s))
res.append(n)
def iprm(n):
    if n <2:
        return False
    for i in range(2,int(n**0.5)+1):
        if n % i == 0:
            return False
    return True

for i in res:
    if iprm(int(i)):
        ans = max(ans,int(i))
print(ans)