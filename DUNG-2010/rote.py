n, m = 3, 4
matrix = []
for i in range(n):
    a = list(map(int,input().split()))
    matrix.append(a)

def choice1(matrix):
    n,m = 3,4

    temp = matrix[0][0]

    for i in range(n - 1):
        matrix[i][0] = matrix[i + 1][0]

    for i in range(m - 1):
        matrix[n - 1][i] = matrix[n - 1][i + 1]

    for i in range(n - 1, 0, -1):
        matrix[i][m - 1] = matrix[i - 1][m - 1]

    for i in range(m - 1, 1, -1):
        matrix[0][i] = matrix[0][i - 1]

    matrix[0][1] = temp
    return matrix

a = choice1(matrix)
for i in a:
    print(*i)