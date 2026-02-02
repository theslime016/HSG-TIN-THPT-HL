with open("PHANHOI.INP",'r') as f:
    k = int(f.readline())
    word = list(map(str,f.read().split()))
res = []
for i in word:
    if not i.isalpha():
        continue
    if not len(i) >= k:
        continue
    res.append(i.upper())
crr = ''
r2 = ''
rr = 1
re2 = -1
if res:
    for i in res:
        if not crr:
            crr = i
        if i == crr:
            rr +=1
        else:
            if rr > re2:
                crr = ''
                re2 = rr
                r2 = i
                rr = 1
with open("PHANHOI.OUT",'w') as f:
    if re2 == -1:
        f.write("-1")
    else:
        f.write(str(r2))
        f.write("\n")
        f.write(str(re2))
