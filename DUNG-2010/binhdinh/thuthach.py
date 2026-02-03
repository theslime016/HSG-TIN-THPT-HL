t = int(input())

def solve(k,a,b):
    dem = 0
    crr = 1
    while True:
        if crr % a == 0 and crr% b == 0:
            dem +=1
        if dem == k:
            print(crr)
            break
        crr +=1

for i in range(t):
    k,a,b = map(int,input().split())
    solve(k,a,b)