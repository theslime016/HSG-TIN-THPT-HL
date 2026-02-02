n = input()
nguyenam = ['u','e','i','a','o']
res = 0 
cting = False
for i in n:
    if not cting:
        temp = 0
        if i == any(i in nguyenam):
            cting = True
    elif cting:
        temp +=1
        if i == any(i in nguyenam):
            res = max(res,temp)
print(res)