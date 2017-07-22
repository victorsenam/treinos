#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

ll A[2123], B[2123], Al[2123];

inline ll fexp(ll x, ll p) {
    ll r = 1;
    for(; p; p >>= 1, x = mod(x * x))
        if(p & 1)
            r = mod(r * x);
    return r;
}
inline ll inv(ll x) { return fexp(x, modn - 2); }

ll fat[2123];

ll ctzinha(int n, int k) {
    ll q = 1;
    for(ll i = n; i <= n + k - 1; i++)
        q = mod(q * i);
    return mod(q * inv(fat[k]));
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, i, j;
    fat[0] = 1;
    for(i = 1; i < 2123; i++)
        fat[i] = mod(fat[i - 1] * ll(i));
    ll a, b, x;
    cin >> n >> a >> b >> x;
    vector<ll> ps;
    ll xx = x;
    for(ll i = 2; i * i <= xx; i++) {
        if(xx % i) continue;
        ll y = 1;
        while(!(xx % i)) xx /= i, y *= i;
        ps.pb(y);
    }
    if(xx != 1) ps.pb(xx);
    int m = ps.size();
    A[(1 << m) - 1] = (b / x) - ((a - 1) / x);
    for(i = (1 << m) - 2; i >= 0; i--) {
        xx = 1;
        for(j = 0; j < m; j++)
            if((i >> j) & 1)
                xx *= ps[j];
        A[i] = (b / xx) - ((a - 1) / xx);
        for(j = i + 1; j < (1 << m); j++)
            if((j | i) == j)
                A[i] -= A[j];
    }
    for(i = 0; i < (1 << m); i++)
        for(j = 0; j <= i; j++)
            if((i | j) == i)
                Al[i] += A[j];
    B[0] = ctzinha(A[0], n);
    for(i = 1; i < (1 << m); i++) {
        B[i] = ctzinha(Al[i], n);
        for(j = 0; j < i; j++)
            if((i | j) == i)
                B[i] += modn - B[j];
        B[i] = mod(B[i]);
    }
    cout << B[(1 << m) - 1] << '\n';
}
