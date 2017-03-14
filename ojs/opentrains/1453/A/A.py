n = int(raw_input())

a = 0
ans = n
z = 2
m = 2

while m <= n and z <= n:
    diff = (n - z%m)//m
    diff -= (z - z%m)//m
    if (a == 1):
        ans += diff
        a = 0
    else:
        ans -= diff
        a = 1

    m *= 2
    z *= 2
    z += 2

print ans
