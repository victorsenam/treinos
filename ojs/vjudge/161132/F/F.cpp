#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int M = 2e6;
const int N = 8*M+8;

struct seg {
    int qt[N], mn[N], lm[N][2], lz[N];

    void printa (int u) {
        printf("[%d,%d] : mn %d qt %d\n", lm[u][0], lm[u][1], mn[u], qt[u]);
    }

    void update (int u) {
        mn[u] += lz[u];
        if (lm[u][0] != lm[u][1]) {
            lz[2*u] += lz[u];
            lz[2*u+1] += lz[u];
        }
        lz[u] = 0;
    }

    int get (int u, int l, int r) {
        update(u);
        if (r < lm[u][0] || lm[u][1] < l)
            return 0;
        if (l <= lm[u][0] && lm[u][1] <= r) {
            //printf("%d - %d = %d | ", lm[u][1] - lm[u][0] + 1, (!mn[u])*qt[u], lm[u][1] - lm[u][0] + 1 - (!mn[u])*qt[u]);
            //printa(u);
            return lm[u][1] - lm[u][0] + 1 - (!mn[u])*qt[u];
        }
        return get(2*u, l, r) + get(2*u+1, l, r);
    }

    ll sum (int u, int l, int r, int x) {
        update(u);
        if (l <= lm[u][0] && lm[u][1] <= r) {
            lz[u] = x;
            update(u);
            //printa(u);
            return mn[u];
        }
        if (r < lm[u][0] || lm[u][1] < l) {
            //printa(u);
            return mn[u];
        }
        mn[u] = min(sum(2*u, l, r, x), sum(2*u+1, l, r, x));
        qt[u] = 0;
        if (mn[u] == mn[2*u])
            qt[u] += qt[2*u];
        if (mn[u] == mn[2*u+1])
            qt[u] += qt[2*u+1];
        //printa(u);
        return mn[u];
    }

    void build (int u, int l, int r) {
        lz[u] = mn[u] = 0;
        qt[u] = r - l + 1;
        lm[u][0] = l; lm[u][1] = r;
        if (l == r) return;
        int mid = (l+r - (l+r<0))/2;
        build(2*u, l, mid);
        build(2*u+1, mid+1, r);
    }
};

int n;
pii v[M];
seg sg;

inline ll sq (ll x) { return x*x; }

bool solve (int k) {
    sg.build(1, -k, k);

    ll rs = 0;

    int ls = -k;

    int i = 0;
    int j = 0;

    while ((i < n || j < n) && ls <= k) {
        int tm, df, y;
        if (j == n || (i < n && v[i].first - k <= v[j].first + k + 1)) {
            df = 1; 
            y = v[i].second;
            tm = v[i].first - k;
            i++;
        } else {
            df = -1;
            y = v[j].second;
            tm = v[j].first + k + 1;
            j++;
        }

        if (tm > ls) {
            tm = min(tm, k + 1);

            ll loc = ll(tm - ls)*(sg.get(1, -k, k));
            rs += loc;
        }

        sg.sum(1, y-k, y+k, df);
        ls = max(ls, tm);
    }

    return (rs != sq(2*k + 1));
}

int main () {
    int tt = 0;
    while (scanf("%d", &n) != EOF && n >= 0) {
        for (int i = 0; i < n; i++)
            scanf("%lld %lld", &v[i].first, &v[i].second);
        sort(v, v+n);

        int lo = 1;
        int hi = M;

        while (lo < hi) {
            int mid = (lo + hi + 1)/2;
            if (solve(mid)) lo = mid;
            else hi = mid-1;
        }

        printf("Case %d: ", ++tt);
        if (lo == M)
            printf("never\n");
        else
            printf("%d\n", lo+1);
    }
}
