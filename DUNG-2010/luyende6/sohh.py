n = int(input())
res = []
cnt = 0
def prm(n):
    if n<2:
        return False
    for i in range(2,int(n**0.5)+1):
        if n % i == 0:
            return False
    return True

for i in range(1,n):
    a = str(i)[::-1]
    if i == 1:
        res.append(i)
    elif prm(i) and prm(int(a)):
        cnt+=1
print(cnt)