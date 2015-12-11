#include <bits/stdc++.h>

using namespace std;

const int N = 10207;
const int M = (N<<1);

typedef long long int num;

struct no {
    int u;
    num d;
    inline bool operator < (const no & ot) const
    { return d > ot.d; }
};

int hd[N], nx[M], to[M], fr[M], es;
num wg[M], ch[M];
bool ty[M];
int n, m, k;
int a, b;
num w, l;
int turn;
int visi[N][2], seen[N][2];
int src, ene, snk;
num dist[N][2];

void djs (int s, bool t) {
    turn++;
    priority_queue<no> pq;
    dist[s][t] = 0;
    no att;
    att.u = s;
    att.d = 0;
    pq.push(att);
    seen[s][t] = turn;

    //printf(" === %d %d ===\n", s, t);
    while (!pq.empty()) {
        att = pq.top();
        pq.pop();
        //printf("%d %I64d\n", att.u, att.d);

        if (visi[att.u][t] == turn || dist[att.u][t] < att.d)
            continue;
        visi[att.u][t] = turn;

        for (int ed = hd[att.u]; ed != -1; ed = nx[ed]) {
            no nex = att;
            nex.d += wg[ed];
            nex.u = to[ed];

            if (seen[nex.u][t] != turn || dist[nex.u][t] > nex.d) {
                seen[nex.u][t] = turn;
                dist[nex.u][t] = nex.d;
                pq.push(nex);
            }
        }
    }
}

int main () {
    scanf("%d %d %d", &n, &m, &k);
    scanf("%d %d %d", &src, &ene, &snk);
    src--; ene--; snk--;
    memset(hd, -1, sizeof hd);
    es = 0;

    for (int i = 0; i < n; i++)
        dist[i][0] = dist[i][1] = LLONG_MAX;

    for (int i = 0; i < m+k; i++) {
        if (i < m) {
            scanf("%d %d %I64d", &a, &b, &w);
            l = w;
        } else
            scanf("%d %d %I64d %I64d", &a, &b, &l, &w);
        a--; b--;
        nx[es] = hd[a]; hd[a] = es; fr[es] = a; to[es] = b; wg[es] = w; ch[es] = l; es++;
    }

    djs(src, 0);
    djs(ene, 1);

    bool md = 1;
    while(md) {
        md = 0;

        for (int ed = m; ed < es; ed++) {
            if (dist[fr[ed]][0] < dist[fr[ed]][1] && wg[ed] != ch[ed]) {
                wg[ed] = ch[ed];
     //           printf("%d %d -> %I64d\n", fr[ed]+1, to[ed]+1, wg[ed]);
                md = 1;
                djs(src, 0);
                djs(ene, 1);
            }
        }
    }
    //printf("========\n");

    if (dist[snk][0] < dist[snk][1]) {
        printf("WIN\n");
        for (int ed = m; ed < es; ed++)
            printf("%d ", wg[ed]);
        printf("\n");
        return 0;
    }

    md = 1;
    while (md) {
        md = 0;

        for (int ed = m; ed < es; ed++) {
            if (dist[fr[ed]][0] <= dist[fr[ed]][1] && wg[ed] != ch[ed]) {
                wg[ed] = ch[ed];
     //           printf("%d %d -> %I64d\n", fr[ed]+1, to[ed]+1, wg[ed]);
                md = 1;
                djs(src, 0);
                djs(ene, 1);
            }
        }
    }

    if (dist[snk][0] == dist[snk][1]) {
        printf("DRAW\n");
        for (int ed = m; ed < es; ed++)
            printf("%d ", wg[ed]);
        printf("\n");
        return 0;
    }

    printf("LOSE\n");
}
