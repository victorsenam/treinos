#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int t, n, m;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> t;

    while (t--) {
        vector<pii> v;
        cin >> n >> m;

        for (int i = 0; i < min(n,m); i++)
            v.push_back(pii(i,i));

        for (int i = max(n,m) - 1; i >= min(n,m); i -= 2)
            v.push_back(pii(i%n,i%m));

        cout << v.size() << endl;
        for (pii a : v)
            cout << a.first << " " << a.second << endl;
    }
}
