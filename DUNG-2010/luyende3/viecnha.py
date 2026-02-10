time = int(input())
n = int(input())
a = []
for i in range(n):
    c = int(input())
    a.append(c)
a = sorted(a)
task = sorted(a)
cnt = 0
for t in task:
    if time >= t:
        time -=t
        cnt +=1
    else:
        break

print(cnt)