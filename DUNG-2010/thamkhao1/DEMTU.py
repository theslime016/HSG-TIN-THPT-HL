a = input()
n = int(input())
cnt = 0
a = a.lower()
for i in a.split():
    if  i.isalpha():
        if len(i) == n:
            cnt+=1
    elif not i.isalnum():
            cntt = 0
            for chr in i:
                 if chr.islower():
                      cntt +=1

            if cntt == n:
                 cnt +=1
                 
print(cnt)