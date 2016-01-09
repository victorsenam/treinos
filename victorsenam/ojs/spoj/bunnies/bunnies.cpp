#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef ll num;

const int N = 3007;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}
#else
#define DEBUG(...) {}
#endif

struct cvx {
    num sa[N], sb[N], st[N];
    int ss;

    inline num numceil (num a, num b)
    { return (a+b-1)/b; }

    inline num inter (int i) {
        if (!i)
            return LLONG_MIN;

        return numceil(sb[i]-sb[i-1], sa[i-1]-sa[i]);
    }

    void insert (num a, num b) {
        sa[ss] = a;
        sb[ss] = b;
        st[ss] = inter(ss);

        while (ss && st[ss] <= st[ss-1]) {
            sa[ss-1] = sa[ss];
            sb[ss-1] = sb[ss];
            ss--;
            st[ss] = inter(ss);
        }
        ss++;
    }

    inline void reset ()
    { ss = 0; }

    num get (num x) {
        int l = upper_bound(st, st+ss, x) - st - 1;
        return sa[l]*x + sb[l];
    }
};

num dp[N][N];
int turn;
int k, n, t;
num v[N];
cvx trick;

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &k);

        for (int i = 0; i < n; i++)
            scanf("%lld", v+i);

        sort(v, v+n);

        for (int i = 0; i <= n; i++)
            dp[0][i] = 0;

        for (int p = 1; p <= k; p++) {
            trick.reset();

            for (int i = p; i <= n; i++) {
                trick.insert(v[i-1], dp[p-1][i-1] - (i-1)*v[i-1]);
                dp[p][i] = trick.get(i);
                for (int j = p-1; j < i; j++) {
                    if (dp[p][i] > (i-j)*v[j] + dp[p-1][j]) {
                        DEBUG("Fail: [%d] : %lld", j, (i-j)*v[j] + dp[p-1][j]);
                    }
                }
                DEBUG("(%d,%d) : %lld", p, i, dp[p][i]);
            }
        }

        printf("%lld\n", dp[k][n]);
    }
}
