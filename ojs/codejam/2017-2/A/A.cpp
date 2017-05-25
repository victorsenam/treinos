#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e2+7;

int ts, n, g, p, tt;

int memo[N][N][N][4];
int visi[N][N][N][4];

int pd (vector<int> qt, int lf) {
    if (qt[1] == 0 && qt[2] == 0 && qt[3] == 0) {
        return 0;
    }
    
    int & me = memo[qt[1]][qt[2]][qt[3]][lf];
    if (visi[qt[1]][qt[2]][qt[3]][lf] == tt)
        return me;
    visi[qt[1]][qt[2]][qt[3]][lf] = tt;

    me = -N;
    vector<int> nw = qt;
    for (int k = 1; k <= 3; k++) {
        if (!qt[k]) continue;
        nw[k]--;
        me = max(me, (!lf) + pd(nw, (p - (k - lf + p)%p)%p));
        nw[k]++;
    }

    return me;
}

int main () {
    scanf("%d", &ts);

    for (tt = 1; tt <= ts; tt++) {
        scanf("%d %d", &n, &p);

        vector<int> qt(4, 0);

        int res = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &g);
            if ((g%p) == 0)
                res++;
            qt[g%p]++;
        }

        printf("Case #%d: %d\n", tt, res + pd(qt, 0));
    }
}
