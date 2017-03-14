#include <cstdio>

#define MAX 2001

int p[MAX], v[MAX];
long long int memo[MAX][MAX];

inline long long int max(long long int a, long long int b) {
    if (a > b) return a;
    return b;
}

long long int knap(int s, int n) {
    if (n < 0 || s < 0) return 0;
    if (memo[s][n] != -1ll) return memo[s][n];

    if (s-p[n] >= 0) memo[s][n] = knap(s-p[n], n-1)+v[n];
    else memo[s][n] = 0;

    memo[s][n] = max(memo[s][n], knap(s, n-1));

 //   printf("(%d,%d) -> %lld\n", s, n, memo[s][n]);
    return memo[s][n];
}

int main () {
    int s, n;
    scanf("%d %d", &s, &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &p[i], &v[i]);

        memo[0][i] = 0ll;
        for (int j = 1; j <= s; j++) {
            memo[j][i] = -1ll;
        }
    }

    printf("%lld\n", knap(s, n-1));
}
