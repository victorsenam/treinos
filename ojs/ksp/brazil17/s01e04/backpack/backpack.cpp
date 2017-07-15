#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int K = 25;
const int N = (1<<K);
int n, m;

ll v[K];
ll w[101];
pii memo[N];

pii pd (int mask) {
    if (mask == 0)
        return pii(0,0);
    
    pii & me = memo[mask];
    if (me.first != -1)
        return me;

    me.first = m+1;
    me.second = 0;

    for (int i = 0; i < n; i++) {
        if (mask&(1<<i)) {
            pii loc = pd(mask^(1<<i));
            
            if (loc.second < v[i]) {
                if (loc.first >= m) continue;
                loc.second = w[loc.first];
                loc.first++;
            }

            loc.second -= v[i];
            if (loc.second < 0)
                continue;

            if (loc.first < me.first || (loc.first == me.first && loc.second > me.second))
                me = loc;
        }
    }

    return me;
}

int main () {
    cin >> n >> m;

    for (int i = 0; i < n; i++)
        cin >> v[i];
    for (int i = 0; i < m; i++)
        cin >> w[i];

    for (int i = 0; i < (1<<n); i++) {
        memo[i].first = -1;
    }

    sort(w, w+m, [] (int i, int j) {
        return w[i] > w[j];
    });

    ll res = pd((1<<n)-1).first; 
    if (res == m+1)
        cout << "NIE" << endl;
    else
        cout << res << endl;
}
