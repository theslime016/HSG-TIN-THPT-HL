n,m = map(int,input().split())
k = int(input())
a = []
b = []
c = []
for i in range(k):
    g,t = map(int,input().split())
    b.append((g,t))
    if g >0 and g<=n:
        if t > 0 and t<=m:
            a.append((g,t))
for i in range(k):
    if b[i] in a:
        if b[i] not in c:
            print("SUCCESS")
            c.append(b[i])
        else:
            print("FAIL")
    else:
        print("INVAID")