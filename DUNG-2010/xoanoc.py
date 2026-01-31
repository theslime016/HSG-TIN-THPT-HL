import itertools
n = input()
for comb in itertools.combinations(n):
    print(*comb)
