n,m = map(int,input().split())
re = 0
for i in range(n):
    re += sum(list(map(int,input().split())))
print(re)