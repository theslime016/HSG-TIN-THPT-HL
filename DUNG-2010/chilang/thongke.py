n = list(map(int,input().split()))
duong = 0
am = 0
for i in n:
    if i > 0:
        duong+= i
    elif i < 0:
        am += i

print(duong,am)
a = (duong+am)/len(n)
print(round(a,2))