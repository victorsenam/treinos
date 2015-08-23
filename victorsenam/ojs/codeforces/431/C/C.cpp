#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 107
#define MOD 1000000007

int memo[N][2];
int n, k, d;

inline int mod (int w) {
    return w%MOD;
}

int pd (int w, bool u) {
    if (w < d && u)
        return 0;
    if (w == 0 && !u) 
        return 1;
    if (w <= 0) 
        return 0;
    if (memo[w][u] != -1) 
        return memo[w][u];

    memo[w][u] = 0;

    for (int i = 1; i <= k; i++) {
        memo[w][u] += pd(w-i, ((i < d)&&u));
        memo[w][u] %= MOD;
    }

 //   debug("(%d,%d) -> %d", w, u, memo[w][u]);
    return memo[w][u];
}

int main () {
    scanf("%d %d %d", &n, &k, &d);

    for (int i = 0; i <= n; i++) {
        memo[i][0] = memo[i][1] = -1;
    }

    printf("%d\n", pd(n, 1));
}
