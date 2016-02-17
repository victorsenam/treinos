#include <bits/stdc++.h>

using namespace std;

const int N = 307;
typedef long long int ll;

int hd[N], to[N], nx[N], wg[N], cf[N], deg[N], es;
bool ch[N];
int turn, us[N];
ll sim, ans, att, dist;
int nch, m, ncf, end;
int ts;
int st[N][3], ss;
int ls, u, d, g, e;

bool choose (int ref, int o_e, int a_e) {
    int o_d = (deg[o_e] + ref - 360)%360 - 180;
    int a_d = (deg[a_e] + ref - 360)%360 - 180;

    if (abs(o_d) != abs(a_d))
        return abs(a_d) < abs(o_d);
    return a_d > o_d;
}

void failed() {
    st[ls][1] = deg[st[ls+1][2]^1];                     
    sim += min(att, dist); // se for pra somar duas vezes
    att = 0;
    ss = ls;
}

int main () {
    ts = 0;
    while (scanf("%d %d %d %lld %d %d %d", &nch, &m, &ncf, &dist, &st[0][0], &end, &st[0][1]) && end) {
        st[0][0]--; end--;
        st[0][1] = (st[0][1]+180)%360;

        es = 2;
        ss = 0;

        memset(ch, 0, sizeof ch);
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
            ed <<= 1;
            ed ^= (to[ed] != to[0]);

            cf[ed] = min(cf[ed], d);
            cf[ed^1] = min(cf[ed^1], wg[ed]-d);
        }
        
        for (int i = 0; i < N; i++) {
            if (!hd[i])
                continue;
            printf("[%c]%d:", (ch[i]?'*':' '), i+1);
            for (int ed = hd[i]; ed; ed = nx[ed])
                printf(" %d(%d,%d)", to[ed]+1, deg[ed], cf[ed]);
            printf("\n");
        }

        int cntt = 108;
        ls = -1;
        while (cntt--) {
            u = st[ss][0];
            d = (st[ss][1] + 180)%360;
            printf("[%d] %d %d %d\n", ss, u+1, d, (st[ss][2]>>1));

            if (ch[u] && ls != ss) {
                ls = ss;
                ++turn;
            }

            g = (e^1);
            for (int ed = hd[u]; ed; ed = nx[ed]) {
                if (ch[u] && us[u] == turn)
                    continue;

                if (choose(d, g, ed))
                    g = ed;
            }

            if (g == (e^1)) {
                failed();
            } else if (att || ch[u]) {
                if (att && ch[u]) {
                failed(); continue;
                } else {
                    att += cf[g];
                    
                    if (att > dist) {
                        sim += cf[g];
                        failed();
                    } else {
                        sim += wg[g];
                        if (wg[g] != cf[g]) {
                            ans += att + wg[g] - cf[g];
                            att = 0;
                        }  

                        ss++;
                        st[ss][0] = to[g];
                        st[ss][1] = deg[g^1];
                        st[ss][2] = g;
                    }
                }
            } else {
                ss++;
                st[ss][0] = to[g];
                st[ss][1] = deg[g^1];
                st[ss][2] = g;

                sim += wg[g];
                ans += wg[g];
            }
        }
    }       
}
