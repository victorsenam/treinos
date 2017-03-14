#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 30007;
const int M = 10*N;

struct node {
    int ds;
    int u;

    bool operator < (const node & ot) const
    { return ds > ot.ds; }
};

int hd[N], to[M], nx[M], wg[M], es;
int n, m;
node aux, nxt;
int t;
int rn[N];
priority_queue<node> pq, q;
int turn;
int visi[N], seen[N], dist[N], clos[N];

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);

        es = 2;
        for (int i = 0; i < n; i++) {
            scanf("%d", rn+i);
            hd[i] = 0;
            clos[i] = INT_MAX;
            visi[i] = seen[i] = 0;
        }
        turn = 0;

        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", to+es, to+es+1, wg+es);
            to[es]--; to[es+1]--;
            wg[es+1] = wg[es];
            
            nx[es] = hd[to[es^1]]; hd[to[es^1]] = es; es++;
            nx[es] = hd[to[es^1]]; hd[to[es^1]] = es; es++;
        }

        int res = 0;

        for (int r = 10; r > 0; r--) {
            for (int i = 0; i < n; i++) {
                if (rn[i] == r) {
                    turn++;
                    aux.u = i;
                    aux.ds = 0;
                    dist[i] = 0;
                    seen[i] = turn;
                    q.push(aux);

                    while (!q.empty()) {
                        aux = q.top();
                        q.pop();

                        if (visi[aux.u] == turn) continue;
                        visi[aux.u] = seen[aux.u] = turn;

                     //   DEBUG("%d important for %d\n", i+1, aux.u+1);
                        res++;

                        for (int ed = hd[aux.u]; ed; ed = nx[ed]) {
                            nxt = aux;
                            nxt.u = to[ed];
                            nxt.ds += wg[ed];


                            if (seen[nxt.u] == turn && dist[nxt.u] <= nxt.ds)
                                continue;
                            if (nxt.ds >= clos[nxt.u])
                                continue;

                            seen[nxt.u] = turn;
                            dist[nxt.u] = nxt.ds;

                            q.push(nxt);
                        }
                    }
                }
            }
            turn++;
            for (int i = 0; i < n; i++) {
                if (rn[i] == r) {
                    clos[i] = 0;
                    aux.u = i;
                    aux.ds = 0;
                    pq.push(aux);
                }
            }

            while (!pq.empty()) {
                aux = pq.top();
                pq.pop();

                if (visi[aux.u] == turn) continue;
                visi[aux.u] = turn;

                for (int ed = hd[aux.u]; ed; ed = nx[ed]) {
                    nxt = aux;
                    nxt.u = to[ed];
                    nxt.ds += wg[ed];

                    if (nxt.ds >= clos[nxt.u])
                        continue;

                    clos[nxt.u] = nxt.ds;

                    pq.push(nxt);
                }
            }
        }
        printf("%d\n", res);
        if (t)
            printf("\n");
    }
}
