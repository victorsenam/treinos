#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

struct itv {
    ll l,r;
    ll a,b;

    bool operator < (itv o) {
        if (l != o.l) return l < o.l;
        if (r != o.r) return r < o.r;
        if (a != o.a) return a < o.a;
        return b < o.b;
    }

    itv expand_cons () {
        itv nw = *this;
        nw.b = 0;
        if (b >= 0) {
            nw.l = l - d;
            nw.r = l + d - 1;
        } else {
            nw.l = r - d + 1;
            nw.r = r + d;
        }
        return nw;
    }

    itv expand_chng () {
        itv nw = *this;
        if (b >= 0) {
            nw.l = l + d;
            nw.r = r + d;
        } else {
            nw.l = l - d;
            nw.r = r - d;
        }
        return nw;
    }
};

const int N = 1e3;

int ts;
ll n, d;
ll v[N];
set<itv> s[2];
itv aux;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> d;
    for (int i = 0; i < n; i++)
        cin >> v[i];

    aux.a = 0;
    aux.b = 0;
    aux.l = aux.r = v[0];

    s[0].clear();
    s[0].insert(aux);

    for (int i = 1; i < n; i++) {
        s[i&1].clear();

        for (itv x : s[0]) {
        }
    }
}
