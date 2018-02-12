s = input()
f = [0]*300
fat = [0]*40

fat[0] = 1;
for i in range(1, len(s) + 2):
    fat[i] = fat[i-1]*i

n = len(s)
for i in range(0, len(s)):
    f[ord(s[i])] += 1

def go():
    sm = fat[n]
    for c in range(ord('a'),ord('z')+1):
        sm = sm // fat[f[c]]
    return sm

res = 0
for i in range(0,len(s)):
    n -= 1
    for c in range(ord('a'),ord(s[i])):
        if (f[c] > 0):
            f[c] -= 1
            res += go()
            f[c] += 1
    f[ord(s[i])] -= 1

print(res+1)
