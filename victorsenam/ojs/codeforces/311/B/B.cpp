// WA TESTE 2

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

int main () {
    scanf("%d %d %d", &n, &m, &p);

    d[0] = 0;
    for (int i = 1; i < n; i++) {
        scanf("%I64d", d+i);
        d[i] += d[i-1];
    }

    pre[0] = 0;
    for (int i = 0; i < m; i++) {
        int h;
        scanf("%d %I64d", &h, t+i);
        t[i] -= d[h-1];
    }

    sort(t, t+m);

    for (int i = 0; i < m; i++) {
        pre[i] = pre[i-!!i] + t[i];
        dp[1][i] = t[i]*num(i+1) - pre[i];
    }

    for (int k = 2; k <= p; k++) {
        ss = 0;
        for (int i = 0; i < m; i++) {
            sa[ss] = -i;
            sb[ss] = dp[k-1][i] + pre[i-!!i];
            st[ss] = inter(ss);
            while (ss && st[ss] <= st[ss-1]) {
                swap(sa[ss], sa[ss-1]);
                swap(sb[ss], sb[ss-1]);
                ss--;
                st[ss] = inter(ss);
            }
            ss++;

            int l = upper_bound(st, st+ss, t[i]) - st - 1;

            dp[k][i] = sa[l]*t[i] + sb[l] + t[i]*i - pre[i];
        }
    }

   printf("%I64d\n", dp[p][m-1]);
}
