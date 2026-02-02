n = input()

nums = []
a = ""

for ch in n:
    if ch.isdigit():
        a += ch
    else:
        if a:
            nums.append(a)
            a = ""

if a:
    nums.append(a)
seen = set()
res = []
for x in nums:
    x = str(int(x))
    if x not in seen:
        seen.add(x)
        res.append(x)

print(res)