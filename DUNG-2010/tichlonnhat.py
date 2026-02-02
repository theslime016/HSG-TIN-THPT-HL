n = int(input())
a = list(map(int,input().split()))
a.sort()
res1 = a[-1]* a[-2]
res2 = a[0] *a[1]
print(max(res1,res2))