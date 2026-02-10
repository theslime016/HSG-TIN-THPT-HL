n = int(input())

def solve(n):
    s = str(n)
    best = curr = s[0]

    for i in range(1, len(s)):
        if s[i] > s[i - 1]:
            curr += s[i]
        else:
            if len(curr) > len(best) or (len(curr) == len(best) and curr > best):
                best = curr
            curr = s[i]

    if len(curr) > len(best) or (len(curr) == len(best) and curr > best):
        best = curr

    return int(best)



for i in range(n):
    a = input()
    print(solve(a))
