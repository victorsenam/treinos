#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 1e3+7;
int n;
set<ll> s;

int main () {
    ll res = 1e18;
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        ll cur;
        cin >> cur;

        auto it = s.upper_bound(cur);
        if (it != s.end())
            res = min(*it - cur, res);

        s.insert(cur);
    }

    cout << res << endl;
}
