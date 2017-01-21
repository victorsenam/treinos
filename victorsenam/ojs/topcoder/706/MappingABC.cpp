#line 2 "MappingABC.cpp"
#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int N = 3e3+3;
const ll MOD = 1e9+7;

int status[N];
ll b, u, m, bm, um;

vector<int> oc[N];
vector<int> t;

void add (int st, int v) {
    if ((st&1) && (st&4)) {
        b += v;
        if (st&2)
            bm += v;
    } else if ((st&1) || (st&4)) {
        u += v;
        if (st&2)
            um += v;
    } else if (st&2) {
        m += v;
    }
}

void printa (int st) {
    for (int k = 1; k < 8; k *= 2)
        printf("%d", !!(st&k));
}

void upd (int i, int j, int k) {
    add(status[k], -1);
    status[k] = 0;

    if (oc[k].empty() || k == t[i] || k == t[j]) return;

    //printf("(%d[%d],%d[%d]) %d from ", i, t[i], j, t[j], k);
    //printa(status[k]);
    //printf(" to ");

    if (oc[k].front() < i)
        status[k] |= 1;
    if (oc[k].back() > j)
        status[k] |= 4;
    
    int p = lower_bound(oc[k].begin(), oc[k].end(), i) - oc[k].begin();
    if (oc[k].begin() + p < oc[k].end() && oc[k][p] < j)
        status[k] |= 2;
    add(status[k], 1);
    //printa(status[k]);
    //printf("\n");
}

ll fexp (ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e&1) r = (r * a)%MOD;
        a = (a*a)%MOD;
        e >>= 1;
    }
    return r;
}

class MappingABC {
    public:
    int countStrings(vector <int> inp) {
        t = inp;
        int n = t.size();
        for (int i = 0; i < n; i++)
            oc[t[i]].push_back(i);
        
        ll res = 0;

        for (int i = 0; i < n; i++) {
            int ls = i;
            b = u = m = bm = um = 0;
            for (int k = 0; k < N; k++)
                status[k] = 0;

            for (int j = i+1; j < n; j++) {
                if (t[i] == t[j]) continue;
                if (oc[t[i]].front() != i) continue;
                if (oc[t[j]].back() != j) continue;

                if (ls != i) {
                    for (; ls < j; ls++)
                        upd(i, j, t[ls]);
                    upd(i, j, t[j]);
                } else {
                    for (int k = 0; k < N; k++)
                        upd(i, j, k);
                }
                ls = j;

                ll loc = (fexp(2, u) * fexp(3, m))%MOD;
                if (bm == 0)
                    loc = (((loc - (fexp(2, u-um+m)))%MOD) + MOD)%MOD;

                res = (res + loc)%MOD;
            }
        }
        return res;
    }
};

// BEGIN CUT HERE
int main () {
    MappingABC obj;
    printf("%d\n", obj.countStrings({7,50,1,50,1,50,1,10,7}));
}
// END CUT HERE
