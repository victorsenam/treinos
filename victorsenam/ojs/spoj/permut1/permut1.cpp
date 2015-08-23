#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 13
#define K 100

int n, k, t;
int memo[N][K];

int pd(int n, int k) {
    if (n == 0) return 0;
    if (k == 0) return 1;
    if (memo[n][k] != -1) return memo[n][k];
    
    memo[n][k] = 0;
    for (int i = 0; i <= min(k, n-1); i++)
        memo[n][k] += pd(n-1, k-i);

    return memo[n][k];
}

int main () {
    scanf("%d", &t);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < K; j++)
            memo[i][j] = -1;

    while (t--) {
        scanf("%d %d", &n, &k);
        printf("%d\n", pd(n, k));
    }
}
