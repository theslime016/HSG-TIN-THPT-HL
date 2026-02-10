s = input()
a = int(input())
n = len(s)
stack = []
for digit in s:
 
    while a > 0 and stack and stack[-1] > digit:
        stack.pop()
        a -= 1
    stack.append(digit)


if a > 0:
    stack = stack[:-a]

res = "".join(stack)

res = res.lstrip('0')

print(res if res else "0")