n, k = map(int, input().split());

fat = [0] * 103
fat[0] = 1;
for i in range(1, 102):
    fat[i] = fat[i - 1] * i

def solve(n, k):
    if(n == 1):
        return [1];
    for fst in range(1, n + 1):
        if(k <= fat[n - 1]):
            ans = solve(n - 1, k);
            for i in range(n - 1):
                if(ans[i] >= fst):
                    ans[i] += 1
            return [fst] + ans
        else:
            k -= fat[n - 1];

p = solve(n, k)
for i in range(n):
    print(p[i], end=' ')
print("")
