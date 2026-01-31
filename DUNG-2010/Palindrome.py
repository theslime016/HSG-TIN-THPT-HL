m = int(input())
a = list(map(int,input().split()))
i = 0
if m <= 1:
    print("YES")
    exit()
while i < m-1 and a[i] < a[i+1]:
    i+=1

while i < m-1 and a[i] > a[i+1]:
    i+=1

if i == m-1:
    print("YES")
else:
    print("NO")
    print(i)