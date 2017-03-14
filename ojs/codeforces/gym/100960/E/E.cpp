#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int M = (1<<15);
const ll MOD = 1e9+7;
ll K, m, l, r, a, b, c;
ll pot[34];
ll memo[M];
bitset<M> ty;

inline ll get (ll j) {
    ll k, i = 0;
    while (j >= M) {
        k = 32-__builtin_clz(j);
        i = pot[K-k+1] - 1 - i;
        j = pot[k] - 1 - j;
    }
    if (ty[j])
        return memo[j] - i;
    else
        return memo[j] + i;
}

int main () {
    pot[0] = 1;
    for (int i = 1; i <= 31; i++)
        pot[i] = (pot[i-1]<<1);
    scanf("%lld %lld %lld %lld %lld %lld %lld", &K, &m, &l, &r, &a, &b, &c);

    memo[0] = ty[0] = 0;
    ll ax = 0, ni;
    for (ll i = 1; i < M; i++) {
        if (i >= pot[ax])
            ax++;
        ni = pot[ax] - 1 - i;
        
        memo[i] = memo[ni];
        ty[i] = !ty[ni];
        if (ty[i])
            memo[i] += pot[K-ax+1] - 1;
        else
            memo[i] -= pot[K-ax+1] - 1;
    }

    ll h = 0, nh, nl, nr;

    while (m--) {
        ll f = 0;

        if (l%2 == 0) {
            if ((r-l+1)&2)
                f = pot[K] - 1;
            if (!(r&1))
                f ^= get(r);
        } else {
            f = (((r - l)>>1) * (pot[K] - 1)) + get(l);
            if (!(r%2))
                f += get(r);
        }

        //debug("[%lld]\n", f);

        nh = ((l ^ r ^ h ^ f) + c) % MOD;
        nl = (((l ^ a ^ nh) % (pot[K] + 1)) % (pot[K]));
        nr = ((r ^ b ^ nh) % (pot[K] - nl)) + nl;

        l = nl; r = nr; h = nh;
    }

    printf("%lld\n", h);
}
