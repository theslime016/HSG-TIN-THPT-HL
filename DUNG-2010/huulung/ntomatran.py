n,m = map(int,input().split())
nlist = []
sonto = []
vtri =[]
for i in range(n):
    nlist.append(list(map(int,input().split())))

def isprm(n):
    if n < 2:
        return False
    for i in range(2,int(n**0.5)+1):
        if n % i == 0:
            return False
    return True


for i in range(n):
    for j in range(m):
        if isprm(nlist[i][j]):
            sonto.append(nlist[i][j])
            vtri.append((i,j))
print(len(sonto))
print(*sonto)
print(*vtri)
print(max(sonto))