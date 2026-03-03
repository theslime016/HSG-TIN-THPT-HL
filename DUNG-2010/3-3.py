# bai 1 xâu đảo ngược
# n = input()
# xau = "".join(i for i in n if i.isalpha())
# so = sum(int(i) for  i in n if i.isdigit())
# print(so)
# print(xau if xau else "-1")


#bài 2 số nguyên tố đặc biệt
# n = int(input())
# a = list(map(int,input().split()))
# def sang(n):
#     snt = [True] * (n+1)
#     snt[0] = snt[1] = False
#     for i in range(2,int(n**0.5)+1):
#         if snt[i]:
#             for j in range(i*i,n+1,i):
#                 snt[j] = False
#     return snt
# cnt = 0
# snt = sang(1000000)
# for i in range(n):
#     so = a[i]
#     if snt[so] == True:
#         if snt[sum(int(i) for i in str(so))] == True:
#             cnt +=1

# print(cnt)


#bài 3 tìm cặp số

# m,n,s = map(int,input().split())
# a = list(map(int,input().split()))
# a.sort()
# max_sum = -1
# L = 0
# R = len(a) - 1

# while L < R:
#     current_sum = a[L] + a[R]
    
#     if current_sum <= s:
#         if current_sum > max_sum:
#             max_sum = current_sum
#         L += 1
#     else:
#         R -= 1
        
# print(max_sum)