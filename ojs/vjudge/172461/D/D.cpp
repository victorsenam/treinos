#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e6+7;

int a[N];
vector<int> f[N];
vector<vector<int> > g;
vector<pii> pqn;
int n, qs;
int t;
int q[N][4];
int opn[N], cls[N];
ll rs[N];
ll bit[N];

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

ll get (int a, int b) {
    return get(b) - get(a);
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        f[a[i]].pb(i);
    }

    t = sqrt(double(n)/log2(n)) + 7;

    for (int i = 1; i <= n; i++) {
        if (f[i].size() > t) {
            g.pb(vector<int>(n+3));
            int k = g.size() - 1;

            for (int j = 0; j <= n; j++)
                g[k][j] = 0;

            for (int j : f[i])
                g[k][j]++;

            for (int j = 0; j <= n; j++) {
                g[k][j] += g[k][j-1];
            }
        } else {
            for (int j : f[i])
                for (int k : f[i])
                    pqn.push_back(pii(j,k));
        }
    }

    sort(pqn.begin(), pqn.end());
    
    cin >> qs;
    for (int i = 0; i < qs; i++) {
        for (int j = 0; j < 4; j++)
            cin >> q[i][j];

        opn[i] = i;
        cls[i] = i;

        for (int j = 0; j < g.size(); j++) {
            rs[i] += ll(g[j][q[i][1]] - g[j][q[i][0]-1])*ll(g[j][q[i][3]] - g[j][q[i][2] - 1]);
        }
    }
    
    sort(opn, opn + qs, [] (int i, int j) {
        return q[i][0] < q[j][0];
    });

    sort(cls, cls + qs, [] (int i, int j) {
        return q[i][1] < q[j][1];
    });

    int op = 0, cl = 0, pq = 0;
    while ((op < qs || cl < qs || pq < pqn.size())) {
        int ty = -1;
        int x = n+1;

        if (op < qs && q[opn[op]][0] < x) {
            x = q[opn[op]][0];
            ty = 0;
        }
        if (pq < pqn.size() && pqn[pq].first < x) {
            x = pqn[pq].first;
            ty = 1;
        }
        if (cl < qs && q[cls[cl]][1] < x) {
            x = q[cls[cl]][1];
            ty = 2;
        }

        if (ty == 0) {
            rs[opn[op]] -= get(q[opn[op]][2]-1, q[opn[op]][3]);
            op++;
        } else if (ty == 1) {
            add(pqn[pq].second, 1);
            pq++;
        } else if (ty == 2) {
            rs[cls[cl]] += get(q[cls[cl]][2]-1, q[cls[cl]][3]);
            cl++;
        } else {
            assert(false);
        }
    }
    
    for (int i = 0; i < qs; i++)
        cout << rs[i] << endl;
}
