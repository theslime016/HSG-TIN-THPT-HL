n,m = map(int,input().split())
a = list(map(int,input().split()))
b = [i for i in a if i < m]
vnt =  0
def iprm(n):
    if n < 2:
        return False
    for i in range(2,int(n**0.5)+1):
        if n%i == 0:
            return False
    return True

for i in b:
    if iprm(i):
        vnt+=1
print(vnt)