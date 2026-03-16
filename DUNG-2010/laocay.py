import time
def cau1():
    n = input()
    while len(str(n)) > 1:
        n = sum(int(i) for i in str(n))
    print(n)

def cau2():
    n = input()
    import re
    res = list(map(int,re.findall(r'\d+',n)))
    print(max(res))

def cau3():
    n = int(input())
    def sang(n):
        snt = [True] *(n+1)
        snt[0] = snt[1] = False
        for i in range(2,int(n**0.5)+1):
            if snt:
                for j in range(i*i,n+1,i):
                    snt[j ] = False
        return snt
    def sang_uoc(n):
        uoc = [0] * (n+1)
        for i in range(1, n+1):
            for j in range(i, n+1, i):
                uoc[j] += 1

        return uoc
    snt = sang(10000000)
    uoc = sang_uoc(n+1)
    cnt = 0
    for i in range(n):
        a = uoc[i]
        if snt[a] == True:
            cnt+=1
    print(cnt)

def cau4():
    a,b = map(int,input().split())
    import bisect
    st = time.perf_counter()
    def isprm(n):
        if n < 2 :
            return False
        if n<=3 :
            return True
        if n % 2  == 0 or n % 3 == 0:
            return False
        for i in range(5,int(n**0.5)+1,6):
            if n % i == 0 or n % (i+2) == 0:
                return False
        return True
    cnt = 0
    def sodoi(n):
        res = []
        for i in range(1,100000):
            s = str(i)
            b = int(s+s[::-1])
            c=int(s+s[-2::-1])
            if b <= n:
                res.append(b)
            else:
                break
            if c <= n:
                res.append(c)
        return res
    doi = sorted(sodoi(b))
    c = bisect.bisect_left(doi,a)
    d = bisect.bisect_right(doi,b)
    for i in range(c,d):
        if isprm(doi[i]):
            cnt +=1
    print(cnt)
    en = time.perf_counter()
    print("time=", en-st)

cau4()
