#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 19

int n, k, a;
int memo[2*N+3][N+3];
int v[2*N];
int t;

int pd (int i, int o) {
    if (i == 2*n && o == 0)
        return 1;
    if (i >= 2*n || o > n || o < 0)
        return 0;
    if (memo[i][o] != -1) return memo[i][o];
    
    if (v[i] == 0 && o > 0) 
        memo[i][o] = pd(i+1, o+1) + pd(i+1, o-1);
    else
        memo[i][o] = pd(i+1, o+1);

    return memo[i][o];
}

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &k);
        for (int i = 0; i < 2*n; i++) {
            v[i] = 0;
            for (int j = 0; j <= n; j++) 
                memo[i][j] = -1;
        }

        for (int i = 0; i < k; i++) {
            scanf("%d", &a);
            a--;
            v[a] = 1;
        }

        printf("%d\n", pd(0, 0));
    }
}
