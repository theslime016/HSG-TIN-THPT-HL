n = input().split()
if n == n[::-1]:
    print("Xâu đối xứng")
else:
    print("Xâu không đối xứng")

chuhua = ''
chuthg= ''
so = ''
for i in n:
    if n.upper():
        chuhua += n
    elif n.lower():
        chuthg += n
    elif n.isdigit():
        so  += n

print(chuhua,chuthg,so)
