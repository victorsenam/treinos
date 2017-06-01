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

const int N = 2e5+7;

int n;
ll a[N];
int p[N], dg[N];
queue<pii> qu;
map<ll, ll> mp[2];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 1; i < n; i++) {
        cin >> p[i];
        p[i]--;
        dg[p[i]]++;
    }

    for (int i = 0; i < n; i++) {
        if (!dg[i])
            qu.push(pii(i,0));
    }

    ll res = 0;
    ll xr = 0;
    while (!qu.empty()) {
        pii u = qu.front();
        qu.pop();
        int i = u.first;
        
        mp[u.second][a[i]]++;
        
        dg[p[i]]--;
        if (!dg[p[i]]) {
            qu.push(pii(p[i], !u.second));
        }

        if (!u.second) {
            xr ^= a[i];
        }
    }

    if (!xr) {
        res += ll(mp[0].size()) * ll(mp[0].size() - 1) / 2;
        res += ll(mp[1].size()) * ll(mp[1].size() - 1) / 2;
    }
        
    for (auto ps : mp[0]) {
        ll x = ps.first;
        ll q = ps.second;

        res += q * ll(mp[1][xr^x]);
    }

    cout << res << endl;
}
