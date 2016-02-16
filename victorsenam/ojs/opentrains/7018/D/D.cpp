#include <bits/stdc++.h>

using namespace std;

const int N = 307;
typedef long long int ll;

int hd[N], to[N], nx[N], wg[N], cf[N], es;
bool ch[N];
int st[N], ss;
int turn, us[N];
ll sim, ans, att;
int nch, m, ncf, dist, end;
int ts;

int main () {
    ts = 0;
    while (scanf("%d %d %d %d %d %d %d", &nch, &m, &ncf, &dist, to+1, &end, deg) && end) {
        to[1]--;
        deg[0] = (deg[0]+180)%360;

        es = 2;
        ss = 0;

        memset(ch, 0, sizeof ch);
        memset(cf, 0, sizeof cf);

        for (int i = 0; i < m; i++) {
            scanf("%d %d %d %d %d", to+es, to+es+1, deg+es+1, deg+es);
            deg[es+1] = deg[es];

            nx[es] = hd[to[es+1]]; hd[to[es+1]] = es;
            nx[es+1] = hd[to[es]]; hd[to[es]] = es+1;

            es += 2;
        }

        st[ss++] = 1;

        while (att || st[ss-1] != end) {
        }
    }
}
