n,m = map(int,input().split())
mtrix = []
mat = []
nto = float('inf')
for i in range(n):
    a = list(map(int,input().split()))
    mat.append(max(a))
    mtrix.append(a)
mat = sorted(mat,reverse=True)
def prm(n):
    if n <2:
        return False
    for i in range(2,int(n**0.5)+1):
        if n % i == 0:
            return False
    return True

def second_largest(matrix):
    global nto
    
    max1 = float('-inf')
    max2 = float('-inf')

    for row in matrix:
        for x in row:
            if x < nto and prm(x):
                nto  = x
            if x > max1:
                max2 = max1
                max1 = x
            elif max2 < x < max1:
                max2 = x

    return max2

print(mat[1],mat[0])
print(second_largest(mtrix))
print(nto)