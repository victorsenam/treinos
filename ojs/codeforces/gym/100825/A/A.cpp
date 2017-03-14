#include <bits/stdc++.h>
using namespace std;
#define lld I64d

typedef long long ll;

const int N = 1007;

ll lim[3];

struct cood {
    ll x[3];

    bool operator < (const cood & ot) const {
        for (int i = 0; i < 3; i++)
            if (x[i] != ot.x[i])
                return x[i] < ot.x[i];
        return 0;
    }

    bool operator == (const cood & ot) const {
        for (int i = 0; i < 3; i++)
            if (x[i] != ot.x[i])
                return 0;
        return 1;
    }

    void print() {
        for (int i = 0; i < 3; i++)
            printf("%lld ", x[i]);
        printf("\n");
    }
};

struct planet {
    ll m;
    ll ini[3];
    ll x[3];
    ll v[3];

    void print () {
        printf("%lld", m);
        for (int i = 0; i < 3; i++) 
            printf(" %lld", ini[i]);
        for (int i = 0; i < 3; i++) 
            printf(" %lld", v[i]);
        printf("\n");
    }

    void advance () {
        for (int i = 0; i < 3; i++)
            x[i] = (x[i] + v[i] + lim[i])%lim[i];
    }

    bool isin () {
        for (int i = 0; i < 3; i++)
            if (x[i] < 0 || x[i] >= lim[i])
                return 0;
        return 1;
    }

    cood gc () {
        cood rt;
        for (int i = 0; i < 3; i++)
            rt.x[i] = x[i];
        return rt;
    }

    bool operator < (const planet & ot) {
        if (m != ot.m)
            return m > ot.m;
        for (int i = 0; i < 3; i++)
            if (ini[i] != ot.ini[i])
                return ini[i] < ot.ini[i];
        return 1;
    }
};

ll intdiv (ll a, ll b) {
    return a/b;
}

int n;
planet v[N];
planet aux[N];
planet r[N];
ll s[3];
int rs;
map<cood, vector<planet> > mp;

int main() {
    scanf("%d", &n);

    for (int i = 0; i < 3; i++)
        scanf("%lld", lim+i);

    for (int i = 0; i < n; i++) {
        scanf("%lld", &v[i].m);       
        for (int j = 0; j < 3; j++) {
            scanf("%lld", &v[i].ini[j]);
            v[i].x[j] = v[i].ini[j];
        }
        for (int j = 0; j < 3; j++)
            scanf("%lld", &v[i].v[j]);
    }

    rs = 0;
    int ls = 0;
    while (ls++ < N+7) {
        mp.clear();
        int nn = 0;
        
        for (int i = 0; i < n; i++) {
            v[i].advance();
            mp[v[i].gc()].push_back(v[i]);
        }
      
        for (pair<cood, vector<planet> > vt : mp) {
            if (vt.second.size() > 1) {
                //vt.first.print();
                planet nx;
                nx.m = 0;
                for (int i = 0; i < 3; i++)
                    nx.v[i] = 0;
                for (planet it : vt.second) {
                    //it.print();
                    nx.m += it.m;
                    for (int i = 0; i < 3; i++)
                        nx.v[i] += it.v[i];
                }

                for (int i = 0; i < 3; i++) {
                    nx.ini[i] = nx.x[i] = vt.first.x[i];
                    nx.v[i] = intdiv(nx.v[i], vt.second.size());
                }
                aux[nn++] = nx;
            } else {
                aux[nn++] = vt.second[0];
            }
        }

        for (int i = 0; i < nn; i++)
            v[i] = aux[i];
        if (n != nn) ls = 0;
        n = nn;
    }

    printf("%d\n", n);
    sort(v, v+n);
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        v[i].print();
    }
}
