n = input().split()
cnt = 0

for i in n:
    for j in i:
        if j.isdigit():
            cnt +=1

print(cnt)
print(" ".join(i.capitalize() for  i in n))