# bài ngày 5/3
#bài 1 đêm số chính phương 
# bài 2 câu 3 đề hưng yên 2025-2026
def bai1():
    import math
    n,m = map(int,input().split())
    
    def generate_squares(n,m):
        return [i * i for i in range(n, math.isqrt(m) + 1)]
    print(sum(generate_squares(n,m)))

def bai2():
    n = input()
    tmp = ''
    res = []
    f = False
    for i in range(len(n)):
        if n[i].isdigit() and f :
            tmp += n[i]
        elif n[i].isdigit() and n[i] != '0':
            f = True
            tmp += n[i]
        else:
            if tmp:
                if tmp == tmp[::-1]:
                    res.append(int(tmp))
                tmp = ''
                f = False
    if tmp:            
        if tmp == tmp[::-1]:
            res.append(int(tmp)) 
    if res:
        print(max(res))
    else:
        print(-1)

# đề tham khảo
def cau1():
    a = list(map(int,input().split()))
    chan = len([i for i in a if i % 2 == 0])
    le = len([i for i in a if i % 2 != 0])
    print(le,chan)
    print(max(a),min(a))

def cau2():
    s = input().strip()

    result = s.replace(',', '')
    result = [i for i in result.split()]
    a = int(input())
    cnt =0
    for i in result:
        if len(i) == a:
            cnt +=1
    print(cnt)

def cau3():
    n,m = map(int,input().split())
    s = 0
    for i in range(n):
        s += sum(list(map(int,input().split())))
    print(s)

def cau4():
    n,m  = map(int,input().split())
    matrix = []
    for i in range(n):
        matrix.append(max(list(map(int,input().split()))))
    a =(sorted(matrix,reverse=True))
    print(a[1],a[0])
cau4()
