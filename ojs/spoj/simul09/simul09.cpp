#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 5007;

int p[N];

struct br {
    int id;
    int v;

    bool operator < (const br & ot) const {
        return p[id] < p[ot.id];
    }
};

int n, m;
char c;
ll a, b;
set<br> s;
set<br>::iterator l, r, it;
br x;

set<br>::iterator create (ll k) {
    br aux;
    aux.id = m;
    aux.v = INT_MAX;
    p[m++] = k;
    it = s.upper_bound(aux);
    --it;
    if (p[it->id] == k) return it;
    aux.v = it->v + (p[aux.id]-p[it->id]);
    s.insert(aux);
}

int main () {
    scanf("%d %d", &m, &n);
    m = 0;
    x.v = 1;
    x.id = 0;
    p[m++] = 1;
    s.insert(x);

    for (int i = 0; i < n; i++) {
        scanf(" %c %lld %lld", &c, &a, &b);
        if (c == 'I') {
            it = create(b);
            x.v = it->v;
            x.id = m;
            p[m++] = a;
            s.erase(it);

            r = create(b+1);
            l = create(a);

            for (it = l; it != r; ++it)
                p[it->id]++;   

            s.insert(x);
        } else {
            l = create(a);
            r = create(b+1);

            ll val = 0;
            for (it = l; it != r;) {
                ll ini = p[it->id];
                ll vl = it->v;
                ++it;
                ll en = vl + (p[it->id]-ini) - 1;

                ll loc = ((en)*(en+1) - (vl)*(vl-1))/2;

                printf("from %d[%d] to %d[%d] : %d\n", vl, ini, en, p[it->id]-1, loc);
                val += loc;
            }
            
            printf("%lld\n", val);
        }
    }
}
