
def bai1():
    n = int(input())
    a = list(map(int,input().split()))
    res = []
    for i in a:
        res.append(sum(int(j) for j in str(i)))
    print(" ".join(str(i) for i in res))

def bai2():
    n = input()
    cnt = 0
    for i in range(3,len(n)+1,3):
        if n[i-3:i] != "MOM":
     
            if n[i-3] != "M":
                cnt +=1
            if n[i-2] != "O":
                cnt +=1
            if n[i-1] != "M":
                cnt +=1
    print(cnt)
def bai3():
    n, m = map(int, input().split())
    
    tong = 0
    mt = 0
    
    for _ in range(n):
        a = 0
        for x in map(int, input().split()):
            if x != 1:
                a += 1
        
        tong += a
        mt = max(mt, a)

    print(tong,mt)
  


def bai4():
    n = int(input())
    a = list(map(int,input().split()))
    res = 0
    def cacuoc(n):

        sum_div = [0] * (n + 1)

        for i in range(1, n + 1):
            for j in range(i, n + 1, i):
                sum_div[j] += 1
                
        return sum_div
    uoc = cacuoc(max(a)+1)
    for i in range(n):
        res += (a[i] * uoc[a[i]])
    print(res)
bai4()