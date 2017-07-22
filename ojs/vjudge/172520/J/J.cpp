#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

struct possi {
    ll s, f;
    int conte;
    ll prev_s;

    bool operator < (possi ot) const {
        return s < ot.s;
    }
};

int n;
ll s, dt;
ll d[N], sn[N], st[N];
ll l, r;
possi v[N];
set<posi> rm[N];

void addpoint (possi p) {
    if (p.f < 0) return;
    while (r < p.s)
        v[++r] = p;
    if (v[p.s].f >= p.f) {
        v[p.s] = p;
        rm[p.conte].erase(
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> s >> dt;
    for (int i = 0; i < n; i++)
        cin >> d[i] >> sn[i] >> st[i];

    l = r = s;
    addpoint(possi({s, 0, -1, -1}));

    int ls = 0;
    int qq = 0;
    for (int dd = 0; dd < N; dd++) {
        int k = ls;
        while (d[k] == dd)
            k++;
        
        vector<int> conts;
        conts.reserve(k-ls+3);
        for (int i = ls; i < k; i++)
            conts.pb(i);

        sort(conts.begin(), conts.end(), [] (int i, int j) {
            return sn[i] < sn[j];
        });

        int ss = 0;
        for (int _i = 0; _i < conts.size(); _i++) {
            int i = conts[_i];
            if (ss && st[i] <= st[ss-1])
                continue;
            conts[ss++] = i;
        }

        vector<possi> pp;
        int _i = -1;
        for (int j = l; j <= r; j++) {
            pp.pb(possi({j, v[j].f/2, v[j].conte, j})); // nao usar contest

            while (_i + 1 < ss && sn[conts[_i+1]] <= j)
                _i++;
            if (_i == -1) continue;
            int i = conts[_i];
            pp.pb(possi({st[i]-v[j].f, v[j].f+dt, i, j})); // usar contest
        }

        for (possi p : pp)
            addpoint(p);

        while (l < r && v[l+1].f == 0)
            l++;

        ls = k;
    }

    stack<posi> ll;
    ll.push(v[r]);
    while (ll.top().conte != -1) {
        posi aux;
        aux.s = ll.top().prev_s;
        ll.push(*(rm[ll.top().conte].find(aux)));
    }

    cout << r << endl;
}
