[n,x] = map(int,input().split(' '))

r = 0
t = 1

for i in range(n):
    [a,b] = map(int,input().split(' '))
    while t + x <= a:
        t += x
    r += b - t + 1
    t = b+1

print(r)
