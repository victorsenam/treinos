typedef long long int num;

const int N = 1000007;

#include <bits/stdc++.h>

using namespace std;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {}/*{fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); }*/
#else
#define DEBUG(...) {}
#endif

struct cvx {
    num sa[N], sb[N], st[N];
    int ss;

    inline num numdiv (num a, num b)
    { return (a+b-1)/b; } // MIN: a/b

    inline num inter (int i) {
        if (!i)
            return LLONG_MIN; // MIN: LLONG_MAX

        return numdiv(sb[i]-sb[i-1], sa[i-1]-sa[i]);
    }

    void insert (num a, num b) {
        if (ss && sa[ss-1] == a) {
            if (sb[ss-1] >= b) // MIN: <=
                return;

            ss--;
        }

        sa[ss] = a;
        sb[ss] = b;
        st[ss] = inter(ss);

        while (ss && st[ss] <= st[ss-1]) { // MIN: >=
            sa[ss-1] = sa[ss];
            sb[ss-1] = sb[ss];
            ss--;
            st[ss] = inter(ss);
        }

        DEBUG("insert (%lld,%lld) at %lld\n", a, b, st[ss]);
        ss++;
    }

    inline void reset()
    { ss = 0; }

    num get (num x) { // da pra deixar linear se os x forem ordenados
        int l = upper_bound(st, st+ss, x) - st - 1; // MIN: comparar decrescente
        DEBUG("get %d (%lld,%lld) for %lld\n", l, sa[l], sb[l], x);
        return sa[l]*x + sb[l];
    }
};
cvx trick;

num v[N], d[N], dp[N];
int n;

int main () {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%lld %lld", v+i, d+i);

    trick.reset();
    dp[n+1] = 0;
    trick.insert(n+1, 0);

    for (num i = n; i >= 0; i--) {
        dp[i] = -trick.get(d[i]) + v[i] + d[i]*i;
        trick.insert(i, -dp[i]);
    }

    printf("%lld\n", dp[0]);
}
