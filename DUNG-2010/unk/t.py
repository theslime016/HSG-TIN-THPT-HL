import math
def prm(n):
    if n<2:
        return False
    if n <= 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    
    for i in range(5,int(math.sqrt(n))+1,6):
        if n % i == 0 or n % (i+2) == 0:
            return False
    return True
for i in range(int(input())):
    print(i,prm(i))