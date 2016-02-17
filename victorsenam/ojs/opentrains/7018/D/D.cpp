#include <bits/stdc++.h>

using namespace std;

const int N = 307;
typedef long long int ll;

int hd[N], to[N], nx[N], wg[N], cf[N], deg[N], es;
bool ch[N];
int st[N], ss;
int turn, us[N];
ll sim, ans, att;
int nch, m, ncf, dist, end;
int ts;

bool choose (int ref, int o_e, int a_e) {
    int o_d = (deg[o_e] + ref - 360)%360 - 180;
    int a_d = (deg[a_e] + ref - 360)%360 - 180;

    if (abs(o_d) != abs(a_d))
        return abs(a_d) < abs(o_d);
    return a_d > o_d;
}

int main () {
    ts = 0;
    while (scanf("%d %d %d %d %d %d %d", &nch, &m, &ncf, &dist, to+1, &end, deg) && end) {
        to[1]--; end--;
        deg[0] = (deg[0]+180)%360;

        es = 2;
        ss = 0;

        memset(ch, 0, sizeof ch);
        for (int i = 0; i < nch; i++) {
            scanf("%d", to);
            ch[to[0]-1] = turn;
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
            ed <<= 1;
            ed ^= (to[ed] != to[0]);

            cf[ed] = min(cf[ed], d);
            cf[ed^1] = min(cf[ed^1], wg[ed]-d);
        }
        
        for (int i = 0; i < N; i++) {
            if (!hd[i])
                continue;
            printf("[%c]%d:", ch[i]?'*':' ', i+1);
            for (int ed = hd[i]; ed; ed = nx[ed])
                printf(" %d(%d,%d)", to[ed]+1, deg[ed], cf[ed]);
            printf("\n");
        }

        sim = ans = att = 0;
        st[ss++] = 1;
        bool back = 0;
        while (42) {
            int e = st[ss-1];

            if (back) { // voltando
                if (att) {
                    att -= wg[e];
                    ss--;
                    sim += wg[e]; // tem que somar de novo em sim?
                    continue;
                } else {
                    e = (st[ss]^1);
                }
            } else if (att) { // tentando checa fim
                if (ch[to[e]]) {
                    back = 1;
                    continue;
                }
            } else if (end == to[e]) { // sucesso
                break;
            } else if (ch[to[e]]) { // escolha (começo)
                ++turn;
            }

            int u = to[e];
            int d = deg[e^1];

            d = (d + 180)%360;

            int g = (e^1);
            for (int ed = hd[u]; ed; ed = nx[ed]) {
                if (ch[u] && us[u] == turn)
                    continue;

                if (choose(d, g, ed))
                    g = ed;
            }

            if (att || ch[u]) {
                if (g == (e^1)) {
                    back = 1;
                    continue;
                } else if (cf[u] != wg[u]) {
                    if (att + cf[u] <= dist) {
                        back = 1;
                        sim += 2*cf[u]; // *2?
                        continue;
                    } else {
                        ans += att;
                        att = 0;
                        sim += wg[g];
                        ans += wg[g];
                        st[ss++] = g;
                    }
                }
            } else {
                sim += wg[g];
                ans += wg[g];
                st[ss++] = g;
            }

            back = 0;
        }
        
        printf("%lld %lld\n", ans, sim);
        for (int i = 1; i < ss; i++)
            printf(" %d", (st[i]>>1));
        printf("\n");
    }
}
