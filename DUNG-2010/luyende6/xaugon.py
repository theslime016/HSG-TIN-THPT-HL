n = input()
def ans(s):
    stack = []
    curr = ""
    i = 0

    while i < len(s):
        if s[i].isalpha():
            curr += s[i]

        elif s[i] == '(':
            stack.append(curr)
            curr = ""

        elif s[i] == ')':
            temp = curr
            curr = stack.pop() + temp

        elif s[i].isdigit():
            curr = curr * int(s[i])

        i += 1

    return curr


print(ans((n)))

