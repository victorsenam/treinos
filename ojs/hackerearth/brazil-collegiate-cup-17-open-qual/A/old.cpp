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

const int N = 2e6;

ll v[N];
multiset<ll> s[2];
ll md;

int n, k;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    if (k == 1) {
        ll rs = v[0];
        for (int i = 1; i < n; i++)
            rs = max(rs, v[i]);
        cout << rs << endl;
        return 0;
    }

    for (int i = 0; i < k; i++)
        s[1].insert(v[i]);

    for (int i = 0; i < (k-1)/2; i++) {
        s[0].insert(*s[1].begin());
        s[1].erase(s[1].begin());
    }

    md = *s[1].begin();
    s[1].erase(s[1].begin());

    ll rs = md;

    for (int i = 0; i + k < n; i++) {
        //print();
        if (s[0].find(v[i]) != s[0].end()) {
            s[0].erase(s[0].find(v[i]));
            s[0].insert(md);
        } else if (s[1].find(v[i]) != s[1].end()) {
            s[1].erase(s[1].find(v[i]));
            s[1].insert(md);
        }

        s[1].insert(v[i+k]);
        s[0].insert(*s[1].begin());
        s[1].erase(s[1].begin());
        md = *s[0].rbegin();
        s[0].erase(prev(s[0].end()));

        rs = max(rs, md);
    }
    cout << rs << endl;
}
