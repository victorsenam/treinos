#include <bits/stdc++.h>
using namespace std;
#define debug if (0)

typedef long long ll;

typedef double num;
const num eps = 1e-8;
const num inf = 1./0.;

const int N = 204;
const int M = N*N;

struct dinic {
    // O(MN^2)
    // BipMatch: O(MN^(1/2))
    // UnitCap: O(min{MV^(2/3),M^(3/2)}
    int hd[N], nx[M], to[M], ht[M], es;
    num fl[M], cp[M];
    int n, src, snk;
    int ds[N], sn[N], tr;
    int qi, qf, qu[N];

    void init ()
    { es = 2; memset(hd, 0, sizeof hd); }

    int connect (int i, int j, num cap, num rcap = 0) {
        to[es] = j; nx[es] = hd[i]; cp[es] = cap; fl[es] = 0; hd[i] = es++;
        to[es] = i; nx[es] = hd[j]; cp[es] = rcap; fl[es] = 0; hd[j] = es++;
        return es - 2;
    }

    bool bfs () {
        tr += 2;
        qi = qf = 0;

        qu[qf++] = snk;
        ds[snk] = 0;
        sn[snk] = tr;

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

        return (sn[src] >= tr);
    }

    num dfs (int u, num flw) {
        if (u == snk || flw <= eps)
            return flw;

        for (int & ed = ht[u]; ed; ed = nx[ed]) {
            int v = to[ed];
            if (cp[ed] - fl[ed] <= eps || sn[v] < tr || ds[v] + 1 != ds[u]) {
                continue;
            }
            num ret = dfs(v, min(flw, cp[ed] - fl[ed]));
            if (ret > eps) {
                fl[ed] += ret;
                fl[ed^1] -= ret;
                return ret;
            }
        }

        return 0;
    }

    void check (num res) {
        for (int i = 0; i < n; i++) {
            num sm = 0;
            for (int ed = hd[i]; ed; ed = nx[ed])
                sm += fl[ed];

            if (i == src)
                assert(abs(res-sm) < eps);
            else if (i == snk)
                assert(abs(res+sm) < eps);
            else
                assert(abs(sm) < eps);
        }
    }

    num maxflow () {
        num res = 0;
        while (bfs()) {
            for (int i = 0; i < n; i++)
                ht[i] = hd[i];
            num val = 0.;
            do {
                res += val;
                val = dfs(src, inf);
            } while (val > eps);
        }

        //check(res);
        return res;
    }
};

int n, m;
double v, a;

int ar[N][2];
double wg[M];
dinic flw;
double m_flu, m_wat, m_mix;
double res[M][2];

double calc (double flu) {
    double wat = m_mix - flu;
    flu /= v;

    return pow(flu, a)*pow(wat, 1.-a);
}

int main () {
    cin >> n >> m >> v >> a;

    flw.init();

    flw.n = n + 1;
    flw.src = 0;
    flw.snk = 3;

    for (int i = 0; i < m; i++) {
        cin >> ar[i][0] >> ar[i][1] >> wg[i];

        flw.connect(ar[i][0], ar[i][1], wg[i], wg[i]);
    }

    int flu = flw.connect(0, 1, inf, 0);
    int wat = flw.connect(0, 2, inf, 0);

    flw.cp[flu] = inf;
    flw.cp[wat] = inf;
    m_mix = flw.maxflow();   
    debug cout << "Mix: " << m_mix << endl;

    memset(flw.fl, 0, sizeof flw.fl);
    flw.cp[flu] = inf;
    flw.cp[wat] = 0;
    m_flu = flw.maxflow();
    debug cout << "Flu: " << m_flu << endl;

    memset(flw.fl, 0, sizeof flw.fl);
    flw.cp[flu] = 0;
    flw.cp[wat] = inf;
    m_wat = flw.maxflow();
    debug cout << "Wat: " << m_wat << endl;

    double lo = m_mix - m_wat;
    double hi = m_flu;

    int iter = 500;
    while (iter--) {
        double q1 = (lo+lo+hi)/3.;
        double q2 = (lo+hi+hi)/3.;

        if (calc(q1) < calc(q2))
            lo = q1;
        else
            hi = q2;
    }

    debug cout << lo << " and " << m_mix - lo << endl;

    memset(flw.fl, 0, sizeof flw.fl);
    flw.cp[flu] = lo;
    flw.cp[wat] = 0;
    assert(abs(flw.maxflow() - lo) < eps);

    for (int i = 2; i <= 2*m; i += 2) {
        res[i][0] = flw.fl[i] / v;
        if (flw.fl[i] < -eps) {
            flw.cp[i+1] -= flw.fl[i+1];
            flw.cp[i] = 0;
        } else if (flw.fl[i] > eps) {
            flw.cp[i] -= flw.fl[i];
            flw.cp[i+1] = 0;
        }
    }

    memset(flw.fl, 0, sizeof flw.fl);
    flw.cp[flu] = 0;
    flw.cp[wat] = m_mix - lo;
    assert(abs(flw.maxflow() - (m_mix - lo)) < eps);

    cout << setprecision(20) << fixed;
    for (int i = 2; i <= 2*m; i += 2) {
        if (res[i][0] < -eps || flw.fl[i] < -eps)
            assert(res[i][0] < eps && flw.fl[i] < eps);
        if (res[i][0] > eps || flw.fl[i] > eps)
            assert(res[i][0] > -eps && flw.fl[i] > -eps);
        cout << res[i][0] << " " << flw.fl[i] << endl;
    }
    cout << calc(lo) << endl;
}
