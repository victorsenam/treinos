#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef unsigned long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int S = 62;

map<ll, int> mp[S];
map<ll, int>::iterator it;

int pd (int s, ll v) {
    v &= ((1ull<<(s)) - 1);

    it = mp[s].find(v);
    if (it != mp[s].end())
        return it->second;
    
    ll bs = 0;
    for (ll u = v; u > 0; u -= (u&-u)) {
        ll x = (u&-u);
        int i = __builtin_ctzll(x) + 1;

        bs |= (1ull<<pd(s - i, v - x));
    }

    int r = __builtin_ctzll(~bs);

    mp[s][v] = r;

    return r;
}

int main () {
    int n, a;
    ll v = (1ull<<S) - 1;

    scanf("%d", &n);
    int res = 0;
    for (int i = 0; i < n; i++) {

        scanf("%d", &a);
        res ^= pd(a, v);
    }
    if (res)
        printf("NO\n");
    else
        printf("YES\n");
}
