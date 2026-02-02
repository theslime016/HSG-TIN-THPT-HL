a = int(input())
n = list(map(int,input().split()))
from collections import Counter
count = Counter(n)
best_val = -float('inf')
max_freq = 0

for val, freq in count.items():
    if freq > max_freq:
        max_freq = freq
        best_val = val
    elif freq == max_freq:
        if val > best_val:
            best_val = val
print(best_val)