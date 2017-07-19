#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

char g[1123];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int i, n, m, k, j;
        cin >> n >> m >> k;
        vector<int> all;
        vector<int> pos, neg;
        ll tot = 0;
        for(i = 0; i < n; i++) {
            cin >> g;
            int off = 0, on = 0;
            for(j = 0; j < m; j++)
                if(g[j] == '*') on++;
                else off++;
            tot += on;
            all.pb(off - on);
            if(off >= on) pos.pb(off - on);
            if(on >= off) neg.pb(off - on);
        }
        sort(pos.begin(), pos.end());
        vector<int> pos2 = pos;
        while(k && !pos.empty()) {
            tot += pos.back();
            k--;
            pos.pop_back();
        }
        if(k & 1) {
            if(!neg.empty() && (pos2.empty() || (*max_element(neg.begin(), neg.end()) >= -pos2.front()))) tot += *max_element(neg.begin(), neg.end());
            else tot -= *min_element(pos2.begin(), pos2.end());
        }
        cout << tot << '\n';
    }
}
