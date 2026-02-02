a = list(map(int,input().split()))
chan = 0
le = 0
mi = 999999
ma = 0

for i in a:
    if i % 2 == 0:
        chan +=1
    else:
        le +=1
    mi = min(mi,i)
    ma = max(ma,i)
print(chan,le)
print(ma,mi)