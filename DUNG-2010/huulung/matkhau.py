s = input().strip()
n = len(s)
valisub = []
for i in range(n):
    for j in range(i+6,n+1):
        sub = s[i:j]
        hsuper = any(c.isupper() for c in sub)
        hslower = any(c.islower() for c in sub)
        hsnumber = any(c.isdigit() for c in sub)
        if hsuper and hslower and hsnumber:
            valisub.append(sub)
print(len(valisub))
print(*valisub)