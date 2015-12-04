// ERRADO, TEM QUE COLOCAR COMBINAÇÕES NO MEIO DA PD, A LOGICA TA ERRADA... (MAS EU SEI ARRUMAR xD)

#include <bits/stdc++.h>

using namespace std;
typedef long long int num;

const int N = 53;
const int K = 103;
const int T = N*N;
const num MOD = 1000000007;

int dist[N][N][3];
int n, k;
int ql, qh;
int qu[T][4], qi, qf;
bool visi[N][N][K][3*N][2];
num memo[N][N][K][3*N][2];

inline num mod (num a)
{ return (a%MOD + MOD)%MOD; }

num pd (int l, int h, int w, int t, bool es, bool ch) {
    if (t < 0)
        return 0;
    if ((l|h) == 0 && !ch)
        return (t == 0);
    
    num & me = memo[l][h][w][t][ch];

    if (visi[l][h][w][t][ch])
        return me;
    visi[l][h][w][t][ch] = 1;

    me = 0;
    if (es) {
        if (w != k)
            me = mod(me + pd(l, h, k, t-1, !es));
        
        if (l && w)
            me = mod(me + mod(l*pd(l-1, h, w-1, t, es)));
        if (h && (w>>1))
            me = mod(me + mod(h*pd(l, h-1, w-2, t, es)));
    } else {
        if (w != k)
            me = mod(me + pd(l, h, k, t-1, !es));

        if ((ql-l) && w)
            me = mod(me + mod((ql-l)*pd(l+1, h, w-1, t, es)));
        if ((qh-h) && (w>>1))
            me = mod(me + mod((qh-h)*pd(l, h+1, w-2, t, es)));
    }

    printf("== %d %d %d %d %d -> %lld\n", l, h, w, t, es, me);
    return me;
}

int main ( ){
    scanf("%d %d", &n, &k);

    k /= 50;

    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        if (a == 50)
            ql++;
        else
            qh++;
    }

    memset(dist, -1, sizeof dist);

    qi = qf = 0;
    qu[qf][2] = 0; qu[qf][0] = ql; qu[qf++][1] = qh;
    dist[ql][qh][0] = 0;

    while (qi < qf) {
        bool ty = qu[qi][2];
        int l = qu[qi][0];
        int h = qu[qi++][1];

        if ((l|h) == 0)
            break;

        if (ty) {
            for (int i = 0; i <= ql-l; i++) {
                if (i > k)
                    break;
                for (int j = 0; j <= qh-h; j++) {
                    if (i+j+j> k)
                        break;
                    if (i == 0 && j == 0)
                        continue;
                    
                    if (dist[l+i][h+j][!ty] != -1)
                        continue;

                    dist[l+i][h+j][!ty] = dist[l][h][ty]+1;
                    qu[qf][2] = 0;
                    qu[qf][0] = l+i;
                    qu[qf++][1] = h+j;
                }
            }
        } else {
            for (int i = 0; i <= l; i++) {
                if (i > k)
                    break;
                for (int j = 0; j <= h; j++) {
                    if (i + 2*j > k)
                        break;
                    if (i == 0 && j == 0)
                        continue;
                    
                    if (dist[l-i][h-j][!ty] != -1)
                        continue;

                    dist[l-i][h-j][!ty] = dist[l][h][ty]+1;
                    qu[qf][2] = 1;
                    qu[qf][0] = l-i;
                    qu[qf++][1] = h-j;
                }
            }
        }
    }

    int d = dist[0][0][0];
    if (d == -1)
        d = dist[0][0][1];
    if (dist[0][0][1] != -1)
        d = min(dist[0][0][1], d);

    printf("%d\n", d);
    printf("%lld\n", pd(ql, qh, k, d, 1, 0));
}
