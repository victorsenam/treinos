#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

const int K = 19;
const int N = (1<<K);
const ll MOD = 1000000007;

struct num {
    int x;
    num (ll v) : x(v) {}
    num (int v) : x(v) {}
    num () {}
    void operator += (num y)
    { x = (ll(x)+ll(y.x))%MOD; }
    void operator *= (num y)
    { x = (ll(x)*ll(y.x))%MOD; }
    void operator -= (num y)
    { x = ((ll(x)-ll(y.x))%MOD+MOD)%MOD; }
    num fexp (ll e) {
        num r(1ll), a(x);
        while (e) {
            if (e&1)
                r *= a;
            a *= a;
            e >>= 1;
        }
        return r;
    }
    void operator /= (num y)
    { *this *= y.fexp(MOD-2); }
};

num ans, loc;
num fat[N];
num p[N], a[N];
num choose (int n, int k) {
    if (k < 0 || n < k) return num(0);
    num r = fat[n]; num q = fat[k];
    q *= fat[n-k]; r /= q;

    printf("(%d %d) = %d\n", n, k, r.x);
    return r;
}

int main () {
    int k;
    scanf("%d", &k);
    num ans(0ll);

    fat[0] = num(1);
    for (int i = 1; i <= (1<<k); i++) {
        fat[i] = fat[i-1];
        fat[i] *= num(i);
    }

    for (int i = 0; i < (1<<k); i++)
        scanf("%lld", &a[i].x);

    for (int j = 1; j <= k; j++) {
        num loc(0ll), tp(0ll);
        for (int i = (1<<(k-j))-1; i < (1<<k); i++) {
            p[i] = choose(i+1, (1<<(k-j)));
            p[i] /= choose((1<<k), (1<<(k-j)));
            p[i] *= a[i];
            tp += p[i];
        }
        for (int i = (1<<(k-j))-1; i < (1<<k); i++) {
            num aux = tp;
            aux -= p[i];
            printf("%d(%d) %d*%d = ", i, a[i], p[i], aux);
            aux *= p[i];
            printf("%d\n", aux);
            loc += aux;
        }
        loc *= num(1ll<<(j-1));
        ans += loc;
        printf("%d -> %d\n", j, loc.x);
    }
    printf("%d\n", ans.x);
}
