#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 2e6+7;
const int Q = 4e3+7;
const ll INF = 1e12;

int ts;

ll n, m, q, cap;
ll hd[N], to[N], nx[N], wg[N], es;

ll dist[N], visi[N];

ll adj[Q][Q];
ll vx[Q][2];

struct vtx {
    int u;
    ll d, g;

    bool operator < (const vtx & ot) const {
        if (d != ot.d)
            return d > ot.d;
        if (g != ot.g)
            return g < ot.g;
        return u < ot.u;
    }
};

struct rep {
    int u;
    ll g;

    rep (vtx x) {
        u = x.u;
        g = x.g;
    }

    bool operator < (const rep & ot) const {
        if (g != ot.g)
            return g < ot.g;
        return u < ot.u;
    }
};

ll djs (int u) {
    map<rep, ll> mp;
    set<rep> vs;
    priority_queue<vtx> pq;

    vtx cur;
    cur.u = u;
    cur.g = 0;
    cur.d = 0;

    pq.push(cur);
    mp[cur] = 0;

    while (!pq.empty()) {
        cur = pq.top();
        pq.pop();

        if (cur.u == q-1)
            return cur.d;

        if (vs.find(cur) != vs.end())
            continue;
        vs.insert(cur);

        //printf("(%lld,%lld) : %lld\n", vx[cur.u][0]+1, cur.g, cur.d);

        for (int v = 0; v < q; v++) {
            vtx nxt = cur;
            nxt.u = v;

            if (adj[cur.u][nxt.u] > cap)
                continue;
            
            nxt.g = cap - adj[cur.u][nxt.u];
            nxt.d = cur.d + (cap - cur.g)*vx[cur.u][1];
            assert(nxt.d >= cur.d);
            if (mp.find(nxt) == mp.end() || mp[nxt] > nxt.d) {
                mp[nxt] = nxt.d;
                pq.push(nxt);
            }

            if (adj[cur.u][nxt.u] < cur.g)
                continue;

            nxt.g = 0;
            nxt.d = cur.d + (adj[cur.u][nxt.u] - cur.g)*vx[cur.u][1];
            assert(nxt.d >= cur.d);
            if (mp.find(nxt) == mp.end() || mp[nxt] > nxt.d) {
                mp[nxt] = nxt.d;
                pq.push(nxt);
            }
        }
    }

    int c = 0;
    while(true) c++;
}

int main () {
    scanf("%d", &ts);
    
    while (ts--) {
        scanf("%lld %lld %lld %lld", &n, &m, &q, &cap);

        for (int i = 0; i < n; i++) {
            hd[i] = 0;
        }

        es = 2;
        for (int i = 0; i < m; i++) {
            int a, b;
            ll w;
            scanf("%d %d %lld", &a, &b, &w);
            a--; b--;

            to[es] = b; nx[es] = hd[a]; wg[es] = w; hd[a] = es++;
            to[es] = a; nx[es] = hd[b]; wg[es] = w; hd[b] = es++;
        }

        for (int i = 0; i < q; i++) {
            scanf("%lld %lld", &vx[i][0], &vx[i][1]);
            vx[i][0]--;
        }

        for (int i = 0; i < 2; i++) {
            scanf("%lld", &vx[q][0]);
            vx[q][0]--;
            vx[q][1] = 100;
            q++;
        }
        vx[q-1][1] = 0;

        for (int k = 0; k < q; k++) {
            priority_queue<vtx> pq;           
            
            for (int i = 0; i < n; i++) {
                dist[i] = INF;
                visi[i] = 0;
            }

            vtx cur;
            cur.u = vx[k][0];
            cur.g = 0;
            cur.d = 0;

            dist[cur.u] = 0;
            pq.push(cur);

            while (!pq.empty()) {
                cur = pq.top();
                pq.pop();

                if (visi[cur.u])
                    continue;
                visi[cur.u] = 1;

                for (int ed = hd[cur.u]; ed; ed = nx[ed]) {
                    vtx nxt = cur;
                    nxt.u = to[ed];
                    nxt.d += wg[ed];

                    if (dist[nxt.u] <= nxt.d)
                        continue;
                    
                    dist[nxt.u] = nxt.d;
                    pq.push(nxt);
                }
            }

            for (int i = 0; i < q; i++) {
                adj[k][i] = dist[vx[i][0]];
                //printf("%lld %lld : %lld\n", vx[k][0]+1, vx[i][0]+1, adj[k][i]);
            }
        }

        printf("%lld\n", djs(q-2));
    }
}
