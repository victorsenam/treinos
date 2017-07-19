#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t, i, j;
    cin >> t;
    while(t--) {
        string s;
        cin >> s;
        set<string> ok;
        int n = s.size();
        for(i = 0; i < n; i++)
            for(j = i; j < n; j++)
                ok.insert(s.substr(i, j - i + 1));
        bool all = true;
        for(i = 0; i < n; i++)
            for(j = i; j < n; j++) {
                string r = s.substr(i, j - i + 1);
                reverse(r.begin(), r.end());
                all = all && ok.count(r);
            }
        if(all) puts("YES");
        else puts("NO");
    }
}
