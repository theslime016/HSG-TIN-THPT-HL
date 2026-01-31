a = ''
for i in range(100):
    n = list(map(int,input().split()))
    if n:
        a = "\n".join(str(sum(n)))

    else:
        print(a)
        break