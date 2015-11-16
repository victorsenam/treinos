#include <bits/stdc++.h>

using namespace std;

const int N = 2007;

int visi[N][N];
int k, n;
int turn;
int memo[N][N];
int a[N];
int lim;

int pd (int ls, int i) {
    if (i == n)
        return 0;
    
    int & me = memo[ls][i];

    if (visi[ls][i] == lim)
        return me;
    visi[ls][i] = lim;

    me = pd(ls, i+1) + 1;
    if (ls == n || (abs(a[i] - a[ls]) <= lim*(i-ls)) )
        me = min(me, pd(i, i+1));

    return me;
}

int main () {
    scanf("%d %d", &n, &k);

    memset(memo, -1, sizeof memo);
    
    int maxi = INT_MIN;
    int mini = INT_MAX;
    for (int i = 0; i < n; i++) {
        scanf("%d", a+i);
        maxi = max(maxi, a[i]);
        mini = min(mini, a[i]);
    }

    int lo = 0;
    int hi = maxi-mini;

    while ( lo < hi ) {
        lim = lo + (hi-lo)/2;
        
        if (pd(n, 0) > k)
            lo = lim+1;
        else
            hi = lim;
    }
    printf("%d\n", lo);
}

