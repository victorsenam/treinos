#include <bits/stdc++.h>
using namespace std;
#define debug if (1)

typedef long long ll;

typedef ll num;
const num eps = 0;
const num inf = LLONG_MAX;

const int N = 1e3+7;
const int M = 2*(N*6 + N + N + 200);

struct dinic {
    // O(MN^2)
    // BipMatch: O(MN^(1/2))
    // UnitCap: O(min{MV^(2/3),M^(3/2)}
    int hd[N], nx[M], to[M], ht[N], es;
    num fl[M], cp[M];
    int n, src, snk;
    int ds[N], sn[N], tr;
    int qi, qf, qu[N];

    void init ()
    { es = 2; memset(hd, 0, sizeof hd); }

    void connect (int i, int j, num cap) {
        to[es] = j; nx[es] = hd[i]; cp[es] = cap; fl[es] = 0; hd[i] = es++;
        to[es] = i; nx[es] = hd[j]; cp[es] = fl[es] = 0; hd[j] = es++;
    }

    bool bfs () {
        tr += 2;
        qi = qf = 0;

        qu[qf++] = snk;
        ds[snk] = 0;

        while (qi < qf) {
            int u = qu[qi++];

            if (sn[u] > tr)
                continue;
            sn[u] = tr+1;

            for (int ed = hd[u]; ed; ed = nx[ed]) {
                if (cp[ed^1] - fl[ed^1] <= eps)
                    continue;
                int v = to[ed];

                if (sn[v] >= tr && ds[v] <= ds[u] + 1)
                    continue;
                sn[v] = tr;
                ds[v] = ds[u] + 1;
                qu[qf++] = v;
            }
        }

        return (sn[src] > tr);
    }

    num dfs (int u, num flw) {
        if (u == snk || flw <= eps)
            return flw;

        for (int & ed = ht[u]; ed; ed = nx[ed]) {
            int v = to[ed];
            if (cp[ed] - fl[ed] <= eps || sn[v] < tr || ds[v] + 1 != ds[u])
                continue;
            num ret = dfs(v, min(flw, cp[ed] - fl[ed]));
            if (ret > eps) {
                fl[ed] += ret;
                fl[ed^1] -= ret;
                return ret;
            }
        }

        return 0;
    }

    void lala () {
        cout << src << " " << snk << endl;
    }

    num maxflow () {
        num res = 0;
        while (bfs()) {
            for (int i = 0; i < n; i++)
                ht[i] = hd[i];
            num val = 0;
            do {
                res += val;
                val = dfs(src, inf);
            } while (val > eps);
        }
        return res;
    }
};

dinic flw;
int ts;
int n;

int main () {
    cin >> ts;
    flw.init();
    flw.n = 10*10*10+2;
    flw.src = flw.n-2;
    flw.snk = flw.n-1;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                for (int m = 0; m < 6; m++) {
                    int ni = i + (m == 0) - (m == 1);
                    int nj = j + (m == 2) - (m == 3);
                    int nk = k + (m == 4) - (m == 5);
                    if (ni < 0 || ni >= 10 || nj < 0 || nj >= 10 || nk < 0 || nk >= 10) {
                        flw.connect(i+j*10+k*100,flw.snk,1);
                    } else {
                        flw.connect(i+j*10+k*100,ni+nj*10+nk*100,1);
                    }
                }
            }
        }
    }

    int ee = flw.es;
    while (ts--) {
        cin >> n;


        memset(flw.fl, 0, sizeof flw.fl);
        flw.es = ee;

        for (int ed = flw.hd[flw.src]; ed; ed = flw.nx[ed]) {
            flw.hd[flw.to[ed]] = flw.nx[flw.hd[flw.to[ed]]];
        }
        flw.hd[flw.src] = 0;

        for (int i = 0; i < n; i++) {
            int x, y, z;
            cin >> x >> y >> z;
            flw.connect(flw.src,x+y*10+z*100,inf);
        }

        cout << flw.maxflow() << endl;
    }
}
