t = int(input())

def uoc(n):
    cnt = 0
    for i in range(1,int(n**0.5)+1):
        if n % i == 0:
            cnt +=1
            if n //i !=i:
                cnt +=1
    return cnt

def thuasonto(n):
    thuaso = []
    while n % 2 == 0:
        thuaso.append(2)
        n = n//2
    for i in range(3,int(n**0.5)+1,2):

        while n % i == 0:
            thuaso.append(i)
            n = n//i
    if n >2:
        thuaso.append(n)
    return thuaso

for i in range(t):
    m = int(input())
    print(uoc(m),"*".join(str(i) for i in thuasonto(m)))