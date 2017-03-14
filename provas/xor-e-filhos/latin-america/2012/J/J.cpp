#include <bits/stdc++.h>

using namespace std;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {}
#else
#define DEBUG(...) {}
#endif

typedef long long ll;

const int N = 1004;

bool cmp_t (ll a, ll b)
{ return a > b; }

struct cvx {
    ll sa[N], sb[N], st[N];
    int ss;


    inline ll numdiv (ll a, ll b)
    { return a/b; }

    inline ll inter (int i) {
        if (!i)
            return LLONG_MAX;

        return numdiv(sb[i]-sb[i-1], sa[i-1]-sa[i]);
    }

    void insert (ll a, ll b) {
        if (ss && sa[ss-1] == a) {
            if (sb[ss-1] <= b)
                return;
            ss--;
        }

        sa[ss] = a;
        sb[ss] = b;
        st[ss] = inter(ss);

        while (ss && st[ss] >= st[ss-1]) {
            sa[ss-1] = sa[ss];
            sb[ss-1] = sb[ss];
            ss--;
            st[ss] = inter(ss);
        }

        ss++;
    }

    inline void reset()
    { ss = 0; }

    ll get (ll x) {
        int l = upper_bound(st, st+ss, x, cmp_t) - st - 1;
        return sa[l]*x + sb[l];
    }
};

int n, k;
ll p[N], w[N];
ll pd[N][N];
ll acc_w[N], acc_p[N];
cvx trick;

int main () {
    while (scanf("%d %d", &n, &k) != EOF) {
        for (int i = 1; i <= n; i++) {
            scanf("%lld %lld", p+i, w+i);
            acc_w[i] = acc_w[i-1] + w[i];
            acc_p[i] = acc_p[i-1] + w[i]*p[i];
        }

        for (int i = 0; i <= n; i++)
            pd[0][i] = acc_w[i]*p[i] - acc_p[i];
        
        for (int q = 1; q <= k; q++) {
            trick.reset();
            pd[q][0] = 0;

            for (int i = 1; i <= n; i++) {
                trick.insert(acc_w[i-1], acc_p[i-1] + pd[q-1][i-1]);
                pd[q][i] = trick.get(-p[i]) + p[i]*acc_w[i] + acc_p[i];
            }
        }

        printf("%lld\n", pd[k][n]);
    }
}
