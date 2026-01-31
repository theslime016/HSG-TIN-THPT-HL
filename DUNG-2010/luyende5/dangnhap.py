from collections import Counter
n = input()
a = len(n)
tt = a *(a-1) // 2
counts = Counter(n)
same = 0
for cnt in counts.values():
    
    if cnt > 1:
        same += cnt *(cnt-1) // 2
ress = tt - same
if same > 0:
    ress +=1

print(ress)