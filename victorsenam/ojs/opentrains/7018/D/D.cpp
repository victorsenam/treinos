#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
const int N = 400;

int ncp, m, ncm, end;
int hd[N], nx[N], to[N], deg[N], wg[N], cf[N], es, res[N];
int ch[N], turn;
bool st;
ll search, path, att, dist;

void sim (int e) {
    if (to[e] == end && !st)
        return 1;

    if (st) {
        if (cf[e] > 0 && cf[e] + att <= dist) {
            search += wg[e];
            path += wg[e];
            st = 0;
            att = 0;
        } else if (att + wg[e] > dist) {
            path += ((dist-att)<<1);
            return 0;
        } else if (ch[to[e]]) {
            path += (wg[e]<<1);
            return 0;
        }
    }

    if (ch[e]) {
        st = 1;
        att = 0;

        bool up_s = 1;
        int up_a = 180;
        do {
            int best = e^1;
            for (int ed = hd[to[e]]; ed; ed = nx[ed]) {
                int at_a = (deg[ed]+360-deg[e])%360;
                int at_s = 0;
                if (at_a < 180)
                    at_s = 1;
                else
                    at_a = 360 - at_a;

                if (make_pair(at_a, at_s) >= make_pair(up_a, up_s))
                    continue;

                
            }
        } while (best != e^1);
    }
}

int main () {
    while (scanf("%d %d %d %lld %d %d %d", &ncp, &m, &ncm, &dist, to+1, &end, deg) && to[1]) {
        memset(hd, 0, sizeof hd);
        turn++;
        to[1]--;
        for (int i = 0; i < ncp; i++) {
            scanf("%d", to);
            ch[to[0]-1] = turn;
        }

        es = 2;
        for (int i = 0; i < m; i++) {
            scanf("%d %d %d %d %d", to+es, to+es+1, deg+es+1, deg+es, wg+es);
            wg[es+1] = wg[es];
            to[es]--; to[es+1]--;

            nx[es+1] = hd[to[es]]; hd[to[es]] = es+1;
            nx[es] = hd[to[es+1]]; hd[to[es+1]] = es;
            es += 2;
        }

        memset(cf, 0, sizeof cf);
        for (int i = 0; i < ncm; i++) {
            int ed, d;
            scanf("%d %d %d", to, &ed, &d);
            ed <<= 1;
            ed ^= (to[ed] != to[0]);

            cf[ed] = max(cf[ed], d);
            cf[ed^1] = max(cf[ed^1], wg[ed]-d);
        }
        
        for (int i = 0; i < N; i++) {
            if (!hd[i])
                continue;
            printf("[");
            if (ch[i])
                printf("*");
            else
                printf(" ");
            printf("]%d:", i+1);

            for (int ed = hd[i]; ed; ed = nx[ed])
                printf(" %d(%d,%d)", to[ed]+1, deg[ed], cf[ed]);
            printf("\n");
        }

        st = search = path = att = 0;
    }
}
