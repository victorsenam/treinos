a = []
fat = [0]*103
for i in range(0, 103):
    a.append([0]*103)

fat[0] = 1
for n in range(0,103):
    if n > 0:
        fat[n] = fat[n-1]*n
    for k in range(0,n+1): 
        if k == 0:
            a[n][k] = 1
        elif k == n:
            a[n][k] = 1
        else:
            a[n][k] = a[n-1][k-1] + a[n-1][k]

n,k,l = map(int,input().split())
l -= 1

res = [0]*n
ans = []

sm = 0
i = 0
for pos in range(0,k):
    while sm + a[n-i-1][k-pos-1] <= l:
        sm += a[n-i-1][k-pos-1]
        i += 1
    ans.append(i+1)
    i += 1

for i in range(k-1):
    print(ans[i],end=" ")
print(ans[k-1])
