n = int(input())

if n == 0:
    print(0)
elif n == 1 or n == 2:
    print(1)
else:
    a = 0
    b = 1
    c = 1
    for i in range(3, n+1):
        d = c + a
        a = b
        b = c
        c = d
    print(c)
