// INCOMPLETO, FAZER ITERATIVO

#include <bits/stdc++.h>

using namespace std;
typedef long long int num;

const int N = 51;
const int K = 101;
const int T = N*N;
const num MOD = 1000000007;

int dist[N][N][3];
num comb[N][N];
int n, k;
int ql, qh;
int qu[T][3], qi, qf;
num pd[N][N][2];

inline num mod (num a)
{ return (a%MOD + MOD)%MOD; }

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
        
    for (int i = 0; i < N; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++)
            comb[i][j] = mod(comb[i-1][j-1] + comb[i-1][j]);
    }

    if (d == -1) {
        printf("-1\n0\n");
        return 0;
    }
    
    pd[0][0][0] = pd[0][0][1] = 1;

    for (int t = 1; t <= k; t++) {
        bool es = ((k-t)&1);
        for (int l = 0; l <= ql; l++) {
            for (int h = 0; h <= qh; h++) {
                printf("=== \n");
                pd[l][h][es] = 0;

                if (es) {
                    for (int nl = l; nl >= 0; nl--) {
                        int cl = l - nl;
                        for (int nh = h; nh >= 0; nh--) {
                            int ch = h - nh;
                            if (!(ch|cl))
                                continue;
                            if ((ch<<1) + cl > k) 
                                break;
                            pd[l][h][es] = mod(pd[l][h][es] + mod(mod(comb[l][cl]*comb[h][ch])*pd[nl][nh][!es]));
                        }
                    }
                } else {
                    for (int nl = l; nl <= ql; nl++) {
                        int cl = nl - l;
                        for (int nh = h; nh <= qh; nh++) {
                            int ch = nh - h;
                            if (!(ch|cl))
                                continue;
                            if ((ch<<1) + cl > k) 
                                break;
                            pd[l][h][es] = mod(pd[l][h][es] + mod(mod(comb[ql-l][cl]*comb[qh-h][ch])*pd[nl][nh][!es]));
                   //         printf("%d %d %d -> ", nl, nh, es);
                   //         printf("%lld ", comb[ql-l][cl]);
                   //         printf("%lld ", comb[qh-h][ch]);
                   //         printf("%lld\n", pd[nl][nh][!es]);
                        }
                    }
                }
                
                printf("%d %d %d[%d]-> %lld\n", l, h, t, es, pd[l][h][es]);
            }
        }
    }

    printf("%d\n", d);
    printf("%I64d\n", pd[ql][qh][0]);
}
