#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 5e2+7;

struct node {
    ll tow, flo;

    bool operator < (const node & ot) const {
        if (tow != ot.tow) return tow < ot.tow;
        return flo < ot.flo;
    }
};

ll ts;
ll n, m, qs;
ll ns;

map<node, int> mp;
node nd[N];
node a[N], b[N];
ll t[N];
ll dist[N][N];

int getnode (node a) {
    if (mp.find(a) == mp.end()) {
        mp[a] = ns;
        nd[ns] = a;
        return ns++;
    } else {
        return mp[a];
    }
}

ll getdist (node x, int i) {
    if (i == -1) return 2e8;
    if (x.tow != nd[i].tow) return 2e8;

    return abs(x.flo - nd[i].flo);
}

int main () {
    scanf("%lld", &ts);

    while (ts--) {
        ns = 0;
        mp.clear();

        ll fll;
        scanf("%lld %lld %lld", &n, &fll, &m);

        a[0].flo = 0;
        for (int i = 0; i < n; i++) {
            a[0].tow = i;
            getnode(a[0]);
        }

        for (int i = 0; i < m; i++) {
            scanf("%lld %lld", &a[i].tow, &a[i].flo);
            scanf("%lld %lld", &b[i].tow, &b[i].flo);
            scanf("%lld", &t[i]);
            a[i].tow--; b[i].tow--; a[i].flo--; b[i].flo--;

            getnode(a[i]);
            getnode(b[i]);
        }

        for (int i = 0; i < ns; i++) {
            for (int j = 0; j < ns; j++) {
                dist[i][j] = 2e8;
                if (i == j)
                    dist[i][j] = 0;
                else if (nd[i].tow == nd[j].tow)
                    dist[i][j] = abs(nd[i].flo - nd[j].flo);
                else if ((nd[i].tow - nd[j].tow) == 1 && !nd[i].flo && !nd[j].flo)
                    dist[i][j] = 1;
                else if (nd[i].tow == 0 && nd[j].tow == n-1 && !nd[i].flo && !nd[j].flo)
                    dist[i][j] = 1;
                else if (nd[i].tow == n-1 && nd[j].tow == 0 && !nd[i].flo && !nd[j].flo)
                    dist[i][j] = 1;
            }
        }

        for (int i = 0; i < m; i++) {
            int na = getnode(a[i]);
            int nb = getnode(b[i]);

            dist[na][nb] = min(dist[na][nb], t[i]);
            dist[nb][na] = min(dist[nb][na], t[i]);
        }

        for (int k = 0; k < ns; k++) {
            for (int i = 0; i < ns; i++) {
                for (int j = 0; j < ns; j++) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    dist[j][i] = min(dist[j][i], dist[i][k] + dist[k][j]);
                }
            }
        }

    /*
        for (int i = 0; i < ns; i++) {
            for (int j = 0; j < ns; j++)
                printf("%lld ", dist[i][j]);
            printf("| %lld %lld\n", nd[i].tow+1, nd[i].flo+1);
        }
    */

        scanf("%lld", &qs);

        while (qs--) {
            node x, y;
            scanf("%lld %lld %lld %lld", &x.tow, &x.flo, &y.tow, &y.flo);
            x.tow--; x.flo--; y.tow--; y.flo--;

            ll res = 2e8;
            
            if (x.tow == y.tow)
                res = min(res, abs(x.flo - y.flo));

            int cx[2] = {-1, -1};
            int cy[2] = {-1, -1};

            for (int i = 0; i < ns; i++) {
                if (getdist(x, cx[0]) > getdist(x, i) && x.flo <= nd[i].flo)
                    cx[0] = i;
                if (getdist(x, cx[1]) > getdist(x, i) && x.flo >= nd[i].flo)
                    cx[1] = i;
                if (getdist(y, cy[0]) > getdist(y, i) && y.flo <= nd[i].flo)
                    cy[0] = i;
                if (getdist(y, cy[1]) > getdist(y, i) && y.flo >= nd[i].flo)
                    cy[1] = i;
            }

    /*
            printf("x : %d : %lld %lld\n", cx[0], nd[cx[0]].tow+1, nd[cx[0]].flo+1);
            printf("x : %d : %lld %lld\n", cx[1], nd[cx[1]].tow+1, nd[cx[1]].flo+1);
            printf("y : %d : %lld %lld\n", cy[0], nd[cy[0]].tow+1, nd[cy[0]].flo+1);
            printf("y : %d : %lld %lld\n", cy[1], nd[cy[1]].tow+1, nd[cy[1]].flo+1);
    */

            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    if (cx[i] != -1 && cy[j] != -1)
                        res = min(res, getdist(x, cx[i]) + getdist(y, cy[j]) + dist[cx[i]][cy[j]]);
                }
            }

            printf("%lld\n", res);
        }
    }
}
