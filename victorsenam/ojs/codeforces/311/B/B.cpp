#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef ll num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;
const int P = 102;

int n, m, p;
num d[N];
num t[N];
num dp[P][N];
num pre[N];

num sa[N];
num sb[N];
num st[N];
int ss;

num inter (int i) {
    if (!i)
        return INT_MIN;

    return (sb[i]-sb[i-1]+sa[i-1]-sa[i]-1)/(sa[i-1]-sa[i]);
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

int main () {
    scanf("%d %d %d", &n, &m, &p);

    d[0] = 0;
    for (int i = 1; i < n; i++) {
        scanf("%I64d", d+i);
        d[i] += d[i-1];
    }

    num add = 0;
    num mint = LLONG_MAX;
    for (int i = 0; i < m; i++) {
        int h;
        scanf("%d %I64d", &h, t+i);
        t[i] -= d[h-1];
        mint = min(mint, t[i]);
    }

    for (int i = 0; i < m; i++) {
        t[i] -= mint;
        add -= t[i];
    }

    sort(t, t+m);

    dp[1][0] = 0;
    for (int i = 1; i <= m; i++) {
        dp[1][i] = t[i-1]*num(i);
    }

    for (int k = 2; k <= p; k++) {
        ss = 0;
        insert(0, dp[k-1][0]);
        dp[k][0] = 0;

        for (int i = 1; i <= m; i++) {
            insert(-i, dp[k-1][i]);

            int l = upper_bound(st, st+ss, t[i-1]) - st - 1;

            dp[k][i] = sa[l]*t[i-1] + sb[l] + t[i-1]*i;
            DEBUG("(%d,%d): %I64d(%I64d)", k, i, dp[k][i], -sa[l]);
        }
    }

    DEBUG("%I64d\n", add);
    printf("%I64d\n", dp[p][m]+add);
}
