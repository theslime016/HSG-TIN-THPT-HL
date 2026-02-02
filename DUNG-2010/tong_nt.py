n,m = map(int,input().split())
matrix = []
res = []
temp = 0
for i in range(n):
    sub = list(map(int,input().split()))
    matrix.append(sub)
def is_Prm(n):
    if n <2:
        return False
    for  i in range(2,int(n**0.5)+1):
        if n % i == 0:
            return False
    return True
for i in range(n):
    for j in range(m):
        temp += matrix[i][j]
        if is_Prm(temp):
            res.append(temp)
print(res)