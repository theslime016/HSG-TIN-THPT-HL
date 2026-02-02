n,m = map(int,input().split())
cnt = 0
def isperm(n):
    if n <2:
        return False
    for  i in range(2,int(n**0.5)+1):
        if n % i == 0:
            return False
        
    return True
for i in range(n+1):
    bit = bin(i)
    if bit.count("1") == m:
        if isperm(i):
            cnt +=1

print(cnt)