#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 207;

ll memo[2][N][N];
int visi[2][N][N], turn;
int t, n;
char str[N];

ll pd (bool t, int i, int j) {
    if (i == j) {
        return str[i]-'0';
    }
    ll & me = memo[t][i][j];

    if (visi[t][i][j] == turn)
        return me;
    visi[t][i][j] = turn;
    
    if (t) me = LLONG_MAX;
    else me = 0;

    for (int k = i+1; k < j; k+=2) {
        ll loc = pd(t, i, k-1);
        if (str[k] == '+')
            loc += pd(t, k+1, j);
        else
            loc *= pd(t, k+1, j);

        if (t) me = min(me, loc);
        else me = max(me, loc);
    }
    return me;
}

int main () {
    scanf("%d", &t);
    while (turn++ < t) {
        scanf(" %s", str);
        n = strlen(str);
        printf("%lld %lld\n", pd(0, 0, n-1), pd(1, 0, n-1));
    }
}
