m,n = map(int,input().split())
matrix = []
for i in range(m):
    a = list(map(int,input().split()))
    matrix.append(a)
solan = int(input())
for i in range(solan):
    b,c = map(int,input().split())
    try:
        if matrix[b][c] == 0:
            matrix[b][c] = 1
            print("Available")
        elif matrix[b][c] == 1:
            print("Not avaible")
    except:
            print("invaid")