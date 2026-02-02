n = int(input())
a = list(map(int,input().split()))
b = []
def iss(n):
    if n <2:
        return False
    for i in range(2,int(n**0.5)+1):
        if n% i == 0:
            return False
    return True

for i in a:
    if iss(i):
        b.append(i)
b = sorted(b,reverse=True)
print(b[0]+b[1])