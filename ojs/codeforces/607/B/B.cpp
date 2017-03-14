#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}
#else
#define DEBUG(...) {}
#endif

const int N = 507;

bool visi[N][N];
int memo[N][N];
int a[N];
int n;

num pd (int i, int j) {
    if (i >= j)
        return 1;

    num & me = memo[i][j];
    if (visi[i][j])
        return me;
    visi[i][j] = 1;

    me = INT_MAX;
    int r = -2;

    if (a[i] == a[j]) {
        me = min(me, pd(i+1,j-1));
        r = -1;
    }

    for (int k = i; k < j; k++) {
        if (pd(i,k) + pd(k+1, j) < me)
            r = k;
        me = min(me, pd(i, k)+pd(k+1, j));
    }

   // DEBUG("(%d,%d) %d [%d]", i, j, me, r);

    return me;
}

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", a+i);
    printf("%d\n", pd(0, n-1));
}
