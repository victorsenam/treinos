#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

int P[3][112];
int sz[3], n;

ll simple(ll n) { return (1ll << n) - 1ll; }

inline int get_mx(int v[3]) {
    int mxi = -1;
    for(int i = 0; i < 3; i++)
        if(v[i] != sz[i] && (mxi == -1 || P[i][v[i]] > P[mxi][v[mxi]]))
            mxi = i;
    return mxi;
}

ll eq(int V[3], int dest) {
    int v[3] = {V[0], V[1], V[2]};
    int mxi = get_mx(v);
    if(mxi == -1) return 0;
    v[mxi]++;
    if(dest == mxi)
        return eq(v, dest);
    else {
        int bk[3] = {v[0], v[1], v[2]};
        return eq(v, 3 - dest - mxi) + 1 + simple(n - bk[0] - bk[1] - bk[2]);
    }
}

ll solve(int V[3], int from, int to) {
    int v[3] = {V[0], V[1], V[2]};
    int mxi = get_mx(v);
    if(mxi == -1) return 0;
    v[mxi]++;
    if(from == mxi) {
        return solve(v, from, 3 - from - to);
    } else if(to == mxi) {
        return solve(v, 3 - from - to, to);
    } else {
        int bk[3] = {v[0], v[1], v[2]};
        int bkk[3] = {v[0], v[1], v[2]};
        return min(eq(v, from), eq(bkk, to)) + 1 + simple(n - bk[0] - bk[1] - bk[2]);
    }
}

int main () {
    scanf("%d", &n);
    for(int k = 0; k < 3; k++) {
        scanf("%d", &sz[k]);
        for(int i = 0; i < sz[k]; i++)
            scanf("%d", &P[k][i]);
        reverse(P[k], P[k] + sz[k]);
    }
    int v[3] = {0, 0, 0};
    printf("%lld\n", solve(v, 0, 2));
}
