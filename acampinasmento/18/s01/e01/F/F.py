n, k = map(int, input().split());

fib = [0] * 100

fib[0] = 1
fib[1] = 2
for i in range(2, 100):
    fib[i] = fib[i - 1] + fib[i - 2]

def solve(n, k):
    if(k == 1):
        return "0" * n
    if(n == 1):
        return "1"
    if(k <= fib[n - 1]):
        return "0" + solve(n - 1, k);
    return "10" + solve(n - 2, k - fib[n - 1]);

print(solve(n, k))
