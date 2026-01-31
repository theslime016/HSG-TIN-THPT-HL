n,m = map(int,input().split())
matrix = []
for i in range(n):
    sub = list(map(int,input().split()))
    matrix.append(sub)
col = len(matrix)
w = len(matrix[0])
print(sum(matrix[i][i]for i in range(min(col,w))))
print(col,w)