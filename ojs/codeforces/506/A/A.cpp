#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 30007;
const int M = 1207;

int memo[N][M];
bool visi[N][M];
int has[N];
int n, d;
int a;
int fix;

int pd (int i, int l) {
    if (i >= N) return 0;
    if (l <= 0) return 0;
    
    int & me = memo[i][l-fix];
    if (visi[i][l-fix]) return me;
    visi[i][l-fix] = 1;

    me = max(pd(i+l+1, l+1), pd(i+l, l));
    me = max(me, pd(i+l-1, l-1));
    me += has[i];

    return me;
}

int main () {
    scanf("%d %d", &n, &d);
    fix = max(0, d-600);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        has[a]++;
    }

    printf("%d\n", pd(d, d));
}
