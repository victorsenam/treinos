#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<ll,ll> pii;
#define fst first
#define snd second

bool cover(pii p, set<pii> &par) {
    auto it = par.lower_bound(pii(p.fst, INT_MIN));
    if(it == par.begin()) return false;
    --it;
    return p.fst > it->fst && p.snd > it->snd;
}

void add(pii p, set<pii> &par) {
    auto it = par.lower_bound(pii(p.fst, INT_MIN));
    if(it != par.end() && it->fst == p.fst && it->snd <= p.snd) return;
    while(it != par.end() && it->fst == p.fst)
        it = par.erase(it);
    while(it != par.end() && it->fst > p.fst && it->snd >= p.snd)
        it = par.erase(it);
    par.insert(pii(p.fst, p.snd));
}

vector<int> oc[3][3123];
int a[3][3123];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    //t = 5;
    cin >> t;
    while(t--) {
        int n, k, i;
        //n = 3000;
        cin >> n;
        for(k = 0; k < 3; k++)
            for(i = 0; i <= n; i++)
                oc[k][i].clear();
        for(k = 0; k < 3; k++)
            for(i = 0; i < n; i++) {
                //a[k][i] = (rand() % n) + 1;
                cin >> a[k][i];
                oc[k][a[k][i]].pb(i);
            }
        vector<pair<int, pii>> vv;
        for(i = 1; i <= n; i++)
            for(int a : oc[0][i])
                for(int b : oc[1][i])
                    for(int c : oc[2][i])
                        vv.pb(make_pair(a, pii(b, c)));
        sort(vv.begin(), vv.end());
        vector<pii> v;
        for(pair<int, pii> x : vv) {
            v.pb(x.second);
            //printf("(%d, %d)\n", x.snd.fst, x.snd.snd);
        }
        vector<set<pii>> par;
        for(pii p : v) {
            for(i = 0; i < par.size(); i++)
                if(!cover(p, par[i]))
                    break;
            //printf("adding (%d, %d) at %d\n", p.fst, p.snd, i);
            if(i == par.size()) par.pb(set<pii>());
            add(p, par[i]);
        }
        cout << par.size() << '\n';
    }
}
