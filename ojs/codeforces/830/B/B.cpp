#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6 + 7;

int n;
int v[N];
ll bit[N];
map<int, set<int> > mp;

void add (int i, int x) {
    for (i += 2; i < N; i+=(i&-i))
        bit[i] += x;
}

ll get (int i) {
    ll x = 0;
    for (i += 2; i > 0; i-=(i&-i))
        x += bit[i];
    return x;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        mp[v[i]].insert(i);
        add(i, 1);
    }

    int cur = 0;
    ll res = 0;
    for (pair<int, set<int> > mm : mp) {
        set<int> & s = mm.second;
        auto it = s.lower_bound(cur);

        if (it == s.begin())
            it = s.end();
        it = prev(it);

        if (*it < cur) {
            res += ll(get(n) - get(cur-1));
            cur = 0;
        }
        res += ll(get(*it) - get(cur-1));
        cur = *it;

        for (int x : s)
            add(x, -1);
    }

    cout << res << endl;
}
