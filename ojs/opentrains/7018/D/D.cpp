#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 307;
const int M = 1000;

int hd[N], to[N], nx[N], wg[N], cf[N], deg[N], es;
bool ch[N];
int turn, us[N];
ll sim, ans, att, dist;
int nch, m, ncf, end;
int ts;
int st[M][4], ss;
int ls, u, d, g, e;

bool choose (int ref, int o_e, int a_e) {
    int o_d = (deg[o_e] - ref + 360)%360;
    if (o_d > 180) o_d = o_d-360;
    int a_d = (deg[a_e] - ref + 360)%360;
    if (a_d > 180) a_d = a_d-360;

    DEBUG("from %d ref %d | o %d -> %d | a %d -> %d\n", to[ref^1], ref, o_e>>1, o_d, a_e>>1, a_d);

    if (abs(o_d) != abs(a_d))
        return abs(a_d) > abs(o_d);
    return a_d < o_d;
}

void failed() {
    st[ls][1] = deg[st[ls+1][2]];
    st[ls][2] = (st[ls+1][2]^1);
    sim += att; // se for pra somar duas vezes
    att = 0;
    ss = ls;
}

int main () {
    ts = 0;
    while (scanf("%d %d %d %lld %d %d %d", &nch, &m, &ncf, &dist, &st[0][0], &end, &st[0][1]) && end) {
        st[0][0]--; end--;
        deg[0] = deg[1] = st[0][1] = (st[0][1]+180)%360;

        es = 2;
        ss = 0;

        memset(ch, 0, sizeof ch);
        memset(hd, 0, sizeof hd);
        for (int i = 0; i < nch; i++) {
            scanf("%d", to);
            ch[to[0]-1] = 1;
        }

        for (int i = 0; i < m; i++) {
            scanf("%d %d %d %d %d", to+es, to+es+1, deg+es+1, deg+es, wg+es);
            cf[es] = cf[es+1] = wg[es+1] = wg[es];
            to[es]--; to[es+1]--;

            nx[es+1] = hd[to[es]]; hd[to[es]] = es+1;
            nx[es] = hd[to[es+1]]; hd[to[es+1]] = es;
            es += 2;
        }

        for (int i = 0; i < ncf; i++) {
            int ed, d;
            scanf("%d %d %d", to, &ed, &d);
            to[0]--;
            ed <<= 1;
            DEBUG("== %d %d\n", to[ed], to[0]);
            ed += (to[ed] == to[0]);

            cf[ed] = min(cf[ed], d);
            cf[ed^1] = min(cf[ed^1], wg[ed]-d);
        }

    /*
        for (int i = 0; i < N; i++) {
            if (!hd[i])
                continue;
            DEBUG("[%c]%d:", (ch[i]?'*':' '), i+1);
            for (int ed = hd[i]; ed; ed = nx[ed])
                DEBUG(" %d(%d,%d)", to[ed]+1, deg[ed], cf[ed]);
            DEBUG("\n");
        }
        for (int i = 2; i < es; i++) {
            DEBUG("%d-%d -> %d/%d\n", to[i^1]+1, to[i]+1, cf[i], wg[i]);
        }
    */

        ls = -1;
        ans = sim = att = 0;
        while (42) {
            u = st[ss][0];
            d = st[ss][1];
            e = st[ss][2];
            DEBUG("[%d] %d %d %d (%d,%d,%d)\n", ss, u+1, d, (e>>1), ans, sim,att);

            if (!att && u == end)
                break;
            if (att && ch[u]) {
                DEBUG("double choice point\n");
                failed(); continue;
            }

            if (ch[u] && ls != ss) {
                ls = ss;
                ++turn;
                DEBUG("change turn %d\n", turn);
                us[e^1] = turn;
            }

            g = (e^1);
            for (int ed = hd[u]; ed; ed = nx[ed]) {
                if (ch[u] && us[ed] == turn) {
                    DEBUG("ignore %d\n", ed>>1);
                    continue;
                }

                if (choose(d, g, ed))
                    g = ed;
            }
            DEBUG("chose %d\n", g>>1);
            if (ch[u])
                us[g] = turn;

            if (g == (e^1)) {
                DEBUG("dead end\n");
                failed();
            } else if (att || ch[u]) {
                DEBUG("choice -> %d + %d\n", att, cf[g]);
                ss++;
                st[ss][0] = to[g];
                st[ss][1] = deg[g^1];
                st[ss][2] = g;
                st[ss][3] = g;
                
                if (att + cf[g] > dist) {
                    DEBUG("gave up\n");
                    sim += (dist-att);
                    att = dist;
                    failed();
                } else {
                    DEBUG("walk\n");
                    sim += wg[g];
                    if (wg[g] != cf[g]) {
                        ans += att + wg[g];
                        att = 0;
                    } else {
                        att += wg[g];
                    }
                }
            } else {
                DEBUG("step\n");
                ss++;
                st[ss][0] = to[g];
                st[ss][1] = deg[g^1];
                st[ss][2] = g;
                st[ss][3] = g;

                sim += wg[g];
                ans += wg[g];
            }
        }

        printf("Case %d:\n", ++ts);
        printf("   Length of hare's route is %d\n", ans);
        printf("   Length of hound's search is %d\n", sim);
        printf("   Route:");
        for (int i = 1; i <= ss; i++)
            printf(" %d", st[i][3]>>1);
        printf("\n\n");
    }       
}
