#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back


const ll MOD = 1e9+7;
ll K, m, l, r, a, b, c;
ll n;
ll pot[34];

ll get (ll i, ll j, ll k) {
    //printf("%lld %lld %lld\n", i, j, k);
        if (k == 0) return i;

            if (j < pot[k-1])
                    return get(i,j,k-1);
                        return get(pot[K-k+1] - 1 - i, pot[k] - 1 - j, k-1);
                        }

                        ll res (ll l, ll r) {
                            ll ans = 0;
                                if (l%2 == 0) {
                                        ll s = (r - l + 1)/2;
                                                ans = (s%2) * (pot[K] - 1);
                                                        if (r%2 == 0)
                                                                    ans ^= get(0, r, K);
                                                                        } else {
                                                                                ll s = (r - (l + 1) + 1)/2;
                                                                                        ans = s * (pot[K] - 1);
                                                                                                ans += get(0, l, K);
                                                                                                        if (r%2 == 0)
                                                                                                                    ans += get(0, r, K);
                                                                                                                        }
                                                                                                                            return ans;
                                                                                                                            }

                                                                                                                            int main () {
                                                                                                                                scanf("%lld %lld %lld %lld %lld %lld %lld", &K, &m, &l, &r, &a, &b, &c);

                                                                                                                                    pot[0] = 1;
                                                                                                                                        for (int i = 1; i <= K+1; i++)
                                                                                                                                                pot[i] = pot[i-1]*2ll;

                                                                                                                                                    ll h = 0;

                                                                                                                                                        for (int i = 0; i < m; i++) {
                                                                                                                                                                ll f = res(l,r);
                                                                                                                                                                        //debug("[%lld]\n", f);

                                                                                                                                                                                ll nh = ((l ^ r ^ h ^ f) + c) % MOD;
                                                                                                                                                                                        ll nl = ((l ^ a ^ nh) % (pot[K] + 1)) % pot[K];
                                                                                                                                                                                                ll nr = ((r ^ b ^ nh) % (pot[K] - nl)) + nl;

                                                                                                                                                                                                        l = nl; r = nr; h = nh;
                                                                                                                                                                                                            }

                                                                                                                                                                                                                printf("%lld\n", h);
                                                                                                                                                                                                                }
