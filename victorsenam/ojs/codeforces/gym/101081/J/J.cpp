#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e5+7;
const int M = 12;

struct point {
    int x, y;
    int u;

    bool operator < (const point & ot) const {
        if (x != ot.x) return x < ot.x;
        return y > ot.y;
    }

    bool beats (const point & ot) const {
        return x > ot.x && y > ot.y;
    }
};

int n, m;
int v[N][M];
int memo[N];
point ps[N];
int opt[N];
set<point> s[N];
set<point>::iterator it;

bool gt (int i, int j) {
    for (int k = 0; k < m; k++)
        if (v[i][k] <= v[j][k]) return 0;
    return 1;
}

int covered (point p, int k) {
    if (k < 0) return p.u;
    it = s[k].upper_bound(p);

    if (it == s[k].begin()) return p.u;
    --it;

    return it->u;
}

bool covers (point p, int k) {
    return p.beats(ps[covered(p, k)]);
}

void build (int u) {
    if (opt[u] != u) build(opt[u]);
    printf("%d ", u+1);
}

int main () {
    scanf("%d %d", &m, &n);

    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++)
            scanf("%d", &v[i][j]);

    int res = 0;

    if (m <= 2) {
        if (m == 1)
            for (int i = 0; i < n; i++)
                v[i][1] = i;
        int st = 0;
        for (int i = 0; i < n; i++) {
            ps[i].x = v[i][0];
            ps[i].y = v[i][1];
            ps[i].u = i;

            int lo = 0;
            int hi = st;
            while (lo < hi) {
                int mid = (lo+hi)/2;
                if (covers(ps[i], mid))
                    lo = mid+1;
                else
                    hi = mid;
            }

            if (lo == st) {
                st++; 
                res = i;
            }
            it = s[lo].insert(ps[i]).first;
            while (next(it) != s[lo].end() && next(it)->beats(ps[i]))
                s[lo].erase(next(it));                
            opt[i] = covered(ps[i], lo-1);
        }
    } else {
        for (int i = 0; i < n; i++) {
            memo[i] = 1;
            opt[i] = i;
            for (int j = 0; j < i; j++) {
                if (gt(i,j) && memo[i] <= memo[j]) {
                    memo[i] = memo[j]+1;
                    opt[i] = j;
                }
            }
            if (memo[i] > memo[res])
                res = i;
        }
    }
    build(res);
}
