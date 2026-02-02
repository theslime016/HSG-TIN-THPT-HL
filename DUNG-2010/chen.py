n,m = map(int,input().split())
a = list(map(int,input().split()))

for i in range(m):
    b,x = map(int,input().split())
    a.insert(b-1,x)

    print(*a)