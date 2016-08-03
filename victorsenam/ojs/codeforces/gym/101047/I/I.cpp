#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int M = 6e4+3;
const int N = 3e4+3;
const int K = 250;

struct uf {
    int uf[K][N];
    int wf[K][N];
    int vs[N], turn;
    int cr;
    bool tm;
    int fr;
    int n;

    void start () {
        if (cr == 0) {
            for (int i = 0; i < n; i++) {
                uf[cr][i] = i;
                wf[cr][i] = 1;
            }
        } else {
            for (int i = 0; i < n; i++) {
                uf[cr][i] = uf[cr-1][i];
                wf[cr][i] = wf[cr-1][i];
            }
        }
    }

    void copy (int to) {
        for (int i = 0; i < n; i++) {
            uf[to][i] = uf[cr][i];
            wf[to][i] = wf[cr][i];
        }
    }
    
    void debug (int f) {
        for (int i = 0; i < n; i++)
            DEBUG("%d ", uf[f][i]);
        DEBUG("\n");
    }

    int find (int i) {
        if (tm && vs[i] != turn) {
            vs[i] = turn;
            uf[cr][i] = uf[fr][i];
            wf[cr][i] = wf[fr][i];
        }
        if (uf[cr][i] == i) return i;
        return uf[cr][i] = find(uf[cr][i]);
    }

    bool join (int i, int j) {
        if ((i = find(i)) == (j = find(j))) return 0;
        if (wf[cr][i] > wf[cr][j]) swap(i, j);
        wf[cr][j] += wf[cr][i];
        uf[cr][i] = j;
        return 1;
    }
};

int t;
int n, m, q, k;
int a[M], b[M], c[M], p[M];
int lo, hi, mid;
short tk[M];
int val;
uf ds;

bool cmp_t (int i, int j) {
    if (c[i] != c[j]) return c[i] < c[j];
    return i < j;
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d %d", &n, &m, &q);
        val = 0;

        for (int i = 0; i < m+q; i++) {
            scanf("%d %d %d", a+i, b+i, c+i);
            a[i]--; b[i]--;
            p[i] = i;
        }

        sort(p, p+m+q, cmp_t);

        lo = 1;
        hi = m+q;
        while (lo < hi) {
            k = (lo+hi)/2;
            if (k*k <= m+q)
                lo = k+1;
            else
                hi = k;
        }
        k = lo;

        ds.n = n;
        ds.cr = 0;
        ds.start();

        for (int _i = 0; _i < m+q; _i++) {
            int i = p[_i];
            ds.cr = _i/k+1;
            if (_i%k == 0) {
                ds.start();
            } 

            tk[i] = ds.cr;
            if (i < m && ds.join(a[i], b[i])) {
                val += c[i];
            }
        }
        
        for (int t = m; t < m+q; t++) {
            lo = 0;
            hi = k;
            //debug_ed(t);

            ds.tm = 0;
            while (lo < hi) {
                mid = (lo+hi+1)/2;

                ds.cr = mid;
                if (ds.find(a[t]) == ds.find(b[t]))
                    hi = mid-1;
                else
                    lo = mid;
            }

            ds.tm = 1;
            ds.fr = lo;
            ds.cr = K-1;
            ds.turn++;

            int i = k*(lo)-1;
            while (ds.find(a[t]) != ds.find(b[t])) {
                i++;
                if (p[i] < t)
                    ds.join(a[p[i]], b[p[i]]);
            }

            //debug_ed(p[i]);

            ds.tm = 0;
            if (c[p[i]] > c[t]) {
                val += c[t] - c[p[i]];
                for (ds.cr = tk[t]; ds.cr <= min(lo, k); ds.cr++)
                    ds.join(a[t], b[t]);
            }
            printf("%d\n", val);
        }

    }
}

