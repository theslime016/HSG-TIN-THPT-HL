n = int(input())
matrix = []
for i in range(n):
    a = list(map(int,input().split()))
    matrix.append(a)
cheo = 0
i = 0
bien = 0
while i < n:
    cheo += matrix[i][i]
    i +=1
for i in range(n):
    bien += matrix[0][i]
for i in range(1,n):
    bien += matrix[i][n-1]
for i in range(n-1):
    bien += matrix[n-1][i]
for i in range(1,n-1):
    bien += matrix[i][0]
print(cheo)
print(bien)