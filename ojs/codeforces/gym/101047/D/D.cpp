#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e5+7;
const int M = 2*N;
const double eps = 1e-9;

ll dist[N];
int visi[N], turn;
int seen[N];
int hd[N], nx[M], to[M], wg[M], es;
int p[N];

struct node {
    int u;
    ll d;

    ll & dist () {
        if (::visi[u] != turn) {
            ::visi[u] = turn;
            ::dist[u] = INT_MAX;
        }
        return ::dist[u];
    }

    bool operator < (const node & ot) const {
        if (d != ot.d)
            return d > ot.d;
        return u > ot.u;
    }
};

int t;
ll n, m;
ll k;
ll mm;

void djs (int ini) {
    priority_queue<node> pq;
    node aux, nxt;
    aux.u = ini;
    aux.d = 0;
    aux.dist() = 0;
    pq.push(aux);

    while (!pq.empty()) {
        aux = pq.top();
        pq.pop();

        if (seen[aux.u] == turn) continue;
        seen[aux.u] = turn;
        
        for (int ed = hd[aux.u]; ed; ed = nx[ed]) {
            nxt = aux;
            nxt.u = to[ed];
            nxt.d += wg[ed];

            if (nxt.dist() <= nxt.d) continue;

            nxt.dist() = nxt.d;

            pq.push(nxt);
        }
    }
}

double expval (int l) {
    return double(mm + k*n)/double(l);
}

bool cmp_t (int i, int j) {
    if (seen[i] != seen[j])
        return seen[i] > seen[j];
    return dist[i] < dist[j];
}

int main () {
    scanf("%d", &t);

    while (t--) {
        turn++;
        scanf("%lld %lld %lld", &n, &m, &k);

        for (int i = 0; i < n; i++) {
            hd[i] = 0;
            p[i] = i;
        }

        es = 2;
        for (int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            a--; b--;
            to[es] = b; nx[es] = hd[a]; wg[es] = c; hd[a] = es++;
            to[es] = a; nx[es] = hd[b]; wg[es] = c; hd[b] = es++;
        }


        djs(n-1);
        sort(p, p+n, cmp_t);

        mm = 0;
        double res = dist[0];
        if (seen[0] != turn)
            res = 1./0.;
        bool ok = 0;
        for (int i = 0; i < n; i++) {
            if (p[i] == 0 || seen[p[i]] != turn) break;
            mm += dist[p[i]];
            res = min(res, expval(i+1));
        }

        printf("%.20f\n", res);
    }
}
