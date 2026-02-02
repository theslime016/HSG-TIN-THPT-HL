n = input()
res = ""

for i in n:
    if i == ' ':
        res += " "
    elif 'a' <= i <= 'z':
        res += chr(ord('z') - (ord(i) - ord('a')))
    elif 'A' <= i <= 'Z':
        res += chr(ord('Z') - (ord(i) - ord('A')))
    elif '0' <= i <= '9':
        res += chr(ord('9') - (ord(i) - ord('0')))
    else:
        res += i
print((res))
a = {}
for i in set(res):
    if i in res:
        a[i] = res.count(i)
a = dict(sorted(a.items()))
for key,val in a.items():
    print(key,':',val)
