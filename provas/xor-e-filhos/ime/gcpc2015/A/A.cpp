#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 20007;
const int S = 16;
const int K = (1<<S);
const int M = 400000;

struct fnode {
    ll u, w;

    bool operator < (const fnode & ot) const{ 
        if (w == ot.w)
            return u > ot.u;
        return w > ot.w;
    }
};

struct snode {
    ll u, w, t;
    unsigned int mask;

    bool operator < (const snode & ot) const {
        return w < ot.w;
    }
};

int n, p, m; 
ll g, t;
int spec[S];

ll visi[N], turn, dist[N], seen[N];
ll svisi[K][S][2], sdist[K][S][2], sseen[K][S][2];
ll cost[S][S];

int to[M], nx[M], hd[N], es;
ll wg[M];

int main () {
    scanf("%d %d %d %lld %lld", &n, &p, &m, &g, &t);

    for (int i = 0; i < p; i++) {
        int a;
        scanf("%d %d", spec+i, &a);
        g -= a;
    }
    spec[p] = 0;
    
    es = 2;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %lld", to+es, to+es+1, wg+es);
        wg[es+1] = wg[es];

        nx[es] = hd[to[es+1]]; hd[to[es+1]] = es;
        nx[es+1] = hd[to[es]]; hd[to[es]] = es+1;
        es += 2;
    }
    
    for (int i = 0; i <= p; i++) {
        turn++;

        priority_queue<fnode> pq;
        dist[spec[i]] = 0;       
        seen[spec[i]] = turn;
        fnode aux;
        aux.u = spec[i];
        aux.w = 0;
        pq.push(aux);

        while (!pq.empty()) {
            fnode u = pq.top();
            pq.pop();
            if (u.w > g)
                break;

            if (visi[u.u] == turn)
                continue;
            visi[u.u] = turn;

            for (int ed = hd[u.u]; ed; ed = nx[ed]) {
                fnode v = u;
                v.u = to[ed];
                v.w += wg[ed];

                if (visi[v.u] == turn) continue;
                if (seen[v.u] == turn && dist[v.u] <= v.w) continue;
                seen[v.u] = turn;
                dist[v.u] = v.w;
                pq.push(v);
            }
        }

        for (int j = 0; j <= p; j++) {
            if (seen[spec[j]] != turn)
                cost[i][j] = g;
            cost[i][j] = dist[spec[j]];
        }
    }
    
    snode aux;
    aux.u = p;
    aux.mask = (1<<p);
    aux.t = 0;
    aux.w = 0;

    priority_queue<snode> pq;
    sdist[aux.mask][aux.u][aux.t] = aux.w;
    sseen[aux.mask][aux.u][aux.t] = 1;
    pq.push(aux);
    while (!pq.empty()) {
        snode u = pq.top();
        pq.pop();

        if (u.w > g)
            break;

        if (svisi[u.mask][u.u][u.t])
            continue;
        svisi[u.mask][u.u][u.t] = 1;
        
        for (int i = 0; i <= p; i++) {
            snode v = u;
            v.mask = (u.mask | (1<<i));
            v.u = i;
            v.w += cost[u.u][v.u];
            
            if (!svisi[v.mask][v.u][v.t] && !(sseen[v.mask][v.u][v.t] && sdist[v.mask][v.u][v.t] <= v.w)) {
                sseen[v.mask][v.u][v.t] = 1;
                sdist[v.mask][v.u][v.t] = v.w;
                pq.push(v);
            }

            if (u.t == 1)
                continue;
            v.t = 1;
            v.w = u.w + t;
            if (svisi[v.mask][v.u][v.t]) continue;
            if (sseen[v.mask][v.u][v.t] && sdist[v.mask][v.u][v.t] <= v.w) continue;
            sseen[v.mask][v.u][v.t]  =1;
            sdist[v.mask][v.u][v.t] = v.w;
            pq.push(v);
        }
    }

    aux.u = p;
    aux.mask = 0;
    for (int i = 0; i <= p; i++)
        aux.mask = (aux.mask | (1<<i));

    if (sseen[aux.mask][aux.u][0] && sdist[aux.mask][aux.u][0] <= g)
        printf("possible without taxi\n");
    else if (sseen[aux.mask][aux.u][1] && sdist[aux.mask][aux.u][1] <= g)
        printf("possible with taxi\n");
    else
        printf("impossible\n");
}
