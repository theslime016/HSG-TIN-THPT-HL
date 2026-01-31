
with open("GIAOHANG.INP",'r') as f:
    n,w = map(int,f.readline().split())
    data = []
    for i in range(n):
        wi,v = map(int,f.readline().split())
        data.append((wi,v))
data = sorted(data,key=lambda x:x[1],reverse=True)
ww = 0
res = 0 
for i in range(n):
    if ww <= w:
        res += data[i][1]
        ww +=data[i][0]
    else:
        res -= data[i-1][1]
        ww -=data[i-1][0]
with open("GIAOHANG.OUT",'w') as w:
    w.write(str(res))