#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 107;

int v[N];
int n;
int memo[N][N];
int visi[N][N];

int pd (int i, int l) {
    if (i == n) return 0;

    int & me = memo[i][l];
    if (visi[i][l]) return me;
    visi[i][l] = 1;
    me = INT_MAX;

    int att = (v[i]&(~l));

    for (int k = 0; k < 4; k++)
        if ((att&k) == k)
            me = min(pd(i+1, k) + !k, me);

    return me;
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);
    printf("%d\n", pd(0, 0));
}
