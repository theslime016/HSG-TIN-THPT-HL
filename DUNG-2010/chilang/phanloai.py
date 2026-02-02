n = list(map(int,input().split()))
duong = []
am = []
for i in n:
    if i > 0:
        duong.append(i)
    elif i < 0:
        am.append(i)

print(*duong)
print(*am)