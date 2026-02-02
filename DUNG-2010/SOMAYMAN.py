with open('SOMAYMAN.INP','r') as f:
    n = int(f.read())

snt = [True] *(1000000)
somayman = []
def is_prm(n):
    
    if n <2:
        return False
    for i in range(2,int(n**0.5)+1):
        if n % i == 0:
            return False
   
    return True
for i in range(1000000):
    temp = 0
    if snt[i]:
        lanto1 = is_prm(i)           
        if lanto1:
            for j in str(i):
                temp += int(j)**2
            
            if is_prm(temp):
      
                somayman.append(i)
print(somayman[-1])