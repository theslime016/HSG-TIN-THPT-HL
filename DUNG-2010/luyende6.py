def bai1():
    n = int(input())
    a = list(map(int, input().split()))
    an = 0
    binh = 0
    l = 0
    r = n-1
    while l < r:
        if a[l] > a[r]:
            an += a[l]
            l +=1
        else:
            an += a[r]
            r -= 1
        if a[l] > a[r]:
            binh += a[l]
            l +=1
        else:
            binh += a[r]
            r -= 1   
    print(an,binh) 

def bai2():
    n = int(input())
    s = input().replace(" ","")
    a = s[:n][::-1]
    b = s[n:][::-1]
    print(a+b)

def bai3():
    n ,m = map(int,input().split())
    a  = []
    for i in range(n):
        a.append(max(list(map(int,input().split()))))
    a = sorted(a, reverse= True)
    print(a[1],a[0])

def bai4():
    n,m = map(int,input().split())
    a = list(map(int,input().split()))
    b = list(map(int,input().split()))
    a = sorted(a)
    b = sorted(b)
    i = 0 
    j = 0
    res =0
    while i < n and j < m :
        if a[i] > b[j]:
            res +=1
            i +=1
            j +=1
        else:
            i +=1
    print(res)
bai4()