#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 2004

int memo[N][N];
int val[N];
int n;

int pd (int i, int j) {
    if (i > j) return 0;
    if (memo[i][j] != -1) return memo[i][j];

    return memo[i][j] = max(val[i]*(i-j+n) + pd(i+1, j), val[j]*(i-j+n) + pd(i, j-1));
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            memo[i][j] = -1;

    for (int i = 0; i < n; i++)
        scanf("%d", val+i);
    
    printf("%d\n", pd(0, n-1));
}
