n=int(input());m=[list(map(int,input().split())) for _ in range(n)];[print(*r) for r in [row[::-1] for row in m[::-1]]]
