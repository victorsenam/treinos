#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+2;
const int M = 2e5+2;

struct posi {
    int s;
    int f;
    int conte;
    int prev_s;
    int from;
};

int n;
int s, dt;
int d[M], sn[M], st[M];
int l, r;
int v[N];
vector<posi> pp;

void addpoint (int p) {
    if (pp[p].s < l || pp[p].f < 0) return;
    while (r < pp[p].s)
        v[++r] = p;
    if (v[pp[p].s] == -1 || pp[v[pp[p].s]].f > pp[p].f) {
        v[pp[p].s] = p;
    }
}

void printa () {
    cout << l << "[";
    for (int i = l; i <= r; i++)
        cout << " " << pp[v[i]].f;
    cout << " ]" << r << endl;
}

int main () {
    memset(v, -1, sizeof v);
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> s >> dt;
    for (int i = 0; i < n; i++)
        cin >> d[i] >> sn[i] >> st[i];

    l = r = s;
    pp.pb(posi({s, 0, -1, -1, -1}));
    addpoint(0);
    //printa();

    int ls = 0;
    int ladd = 1;
    for (int dd = 0; dd < N; dd++) {
        int k = ls;
        while (d[k] == dd)
            k++;
        
        vector<int> conts;
            for (int i = ls; i < k; i++)
            conts.pb(i);

        sort(conts.begin(), conts.end(), [] (int i, int j) {
            return sn[i] < sn[j];
        });

        int ss = 0;
        for (int _i = 0; _i < conts.size(); _i++) {
            int i = conts[_i];
            if (ss && st[i] <= st[conts[ss-1]])
                continue;
            conts[ss++] = i;
        }
        //conts.resize(ss);

        int _i = -1;
        for (int j = l; j <= r; j++) {
            if (j != r && pp[v[j]].f == pp[v[j+1]].f)
                continue;
            pp.pb(posi({j, pp[v[j]].f/2, pp[v[j]].conte, j, pp[v[j]].from})); // nao usar contest

            while (_i + 1 < ss && sn[conts[_i+1]] <= j)
                _i++;
            if (_i == -1) continue;
            int i = conts[_i];
            pp.pb(posi({st[i]-(pp[v[j]].f), (pp[v[j]].f)+dt, i, j, v[j]})); // usar contest
        }

        while (ladd < pp.size())
            addpoint(ladd++);

        while (l < r && pp[v[l+1]].f == 0)
            l++;

        for (int j = l; j <= r; j++)
            if (j != r && pp[v[j]].f > pp[v[j+1]].f)
                pp[v[j]].f = pp[v[j+1]].f;

        //printa();
        ls = k;
    }

    stack<int> ll;
    ll.push(v[r]);
    while (pp[ll.top()].from != -1) {
        ll.push(pp[ll.top()].from);
    }

    cout << r << " " << ll.size() - 1 << endl;
    ll.pop();
    while (ll.size()) {
        cout << pp[ll.top()].conte + 1 << " ";
        ll.pop();
    }
    cout << endl;
}
