#include <bits/stdc++.h>

using namespace std;

typedef long double num;
typedef long long int ll;

const int N = 107;
const int K = 6;

int hp[2];
int vp[N];
int gs, ps;
num pp;
int di[N][N];
num p[N][N][K];
bool visi[N][N];
num memo[N][N];
num pe;
int de;
num choose[K][K];

num pd (int pl, int en) {
    if (en <= 0)
        return 1.;
    if (pl <= 0)
        return 0.;

    num & me = memo[pl][en];
    if (visi[pl][en])
        return me;
    visi[pl][en] = 1;

    me = 0.;
    for (int i = 0; i < gs; i++) {
        for (int j = 0; j < ps; j++) {
            num loc = pd(pl-de, en)*pe*p[i][j][0];

            for (int k = 1; k <= vp[i]; k++)
                loc += p[i][j][k]*( pd(pl, en-k*di[i][j])*(1.-pe) + pd(pl-de, en-k*di[i][j])*pe );
            
            loc /= (1. - (1.-pe)*p[i][j][0]);
            me = max(me, loc);
        }
    }
    return me;
}

int main () {
    freopen("whats.in", "r", stdin);
    freopen("whats.out", "w", stdout);
    scanf("%d %d", hp, hp+1);
    scanf("%d %d", &gs, &ps);

    for (int i = 0; i < K; i++)
        choose[i][0] = 1.;
    for (int i = 1; i < K; i++) {
        choose[i][i] = 1.;
        for (int j = i+1; j < K; j++)
            choose[j][i] = choose[j-1][i-1] + choose[j-1][i];
    }

    for (int i = 0; i < gs; i++) {
        scanf("%d", vp+i);
        for (int j = 0; j < ps; j++) {

            scanf("%Lf %d", &pp, &di[i][j]);
            pp *= .01;
            num acc = 1.;
            num sum = 0.;

            p[i][j][0] = 1.;
            for (int k = 1; k <= vp[i]; k++)
                p[i][j][k] = p[i][j][k-1]*pp;

            for (int k = vp[i]; k >= 0; k--) {
                p[i][j][k] *= acc*choose[vp[i]][k];
                sum += p[i][j][k];
                acc *= (1.-pp);
            }
        }
    }

    scanf("%Lf %d", &pe, &de);
    pe *= .01;

    printf("%.20Lf\n", pd(hp[0], hp[1]));
}
