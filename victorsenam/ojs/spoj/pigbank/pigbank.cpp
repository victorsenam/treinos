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

#define N 500
#define W 10000

int n, t, e, f;
int v[N];
int w[N];
int memo[W][N];

int pd (int p, int i) {
    if (p == 0) return 0;
    if (p < 0 || i >= n) return -1;
    if (memo[p][i] != -2) return memo[p][i];

    int a;

    memo[p][i] = pd(p, i+1);
    a = pd(p-w[i], i);

    if (a == -1) return memo[p][i];
    if (memo[p][i] == -1) return memo[p][i] = a + v[i];
    return memo[p][i] = min(memo[p][i], a+v[i]);
}

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &e, &f);
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d %d", v+i, w+i);
        
        if (f < e) {
            printf("This is impossible.\n");
            continue;
        }

        for (int i = 0; i <= f-e; i++)
            for (int j = 0; j < n; j++)
                memo[i][j] = -2;

        if(pd(f-e, 0) == -1) printf("This is impossible.\n");
        else printf("The minimum amount of money in the piggy-bank is %d.\n", pd(f-e, 0));
    }
}
