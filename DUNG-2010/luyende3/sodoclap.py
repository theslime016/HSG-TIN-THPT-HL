def solve(n):
    curr = n + 1
    while True:
        s = str(curr)
        if len(s) > 10: return -1 
        seen = set()
        idx = -1
        for i, c in enumerate(s):
            if c in seen:
                idx = i
                break
            seen.add(c)
            
        if idx == -1: return curr 
 
        curr = (int(s[:idx+1]) + 1) * (10 ** (len(s) - 1 - idx))

print(solve(int(input()))) 