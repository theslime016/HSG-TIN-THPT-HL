n = list(map(int,input().split()))
res = []

def is_prm(n):
    if n <2:
        return False
    for i in range(2,int(n**0.5)+1):
        if n%i == 0:
            return False
        
    return True

for i in n:
    if is_prm(i):
        res.append(i)

print(*res)
print(sum(res))