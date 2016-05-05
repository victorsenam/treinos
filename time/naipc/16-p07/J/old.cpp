#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 60;
const int M = 50000;
int n;
int p[N];
int hd[N], nx[M], to[M], pr[M], es;

bool cmp (int cr, int nw, int keep) {
    if (cr == nw) return 1;
    if (to[hd[cr]] == to[hd[nw]]) {
        if (cr == keep) return 0;
        if (nw == keep) return 1;
        return cmp(pr[cr], pr[nw], keep);
    }
    
    return to[hd[nw]] > to[hd[cr]];
}

int main () {
    int turn = 0;
    while (scanf("%d", &n) != EOF) {
        memset(hd, 0, sizeof hd);
        memset(pr, 0, sizeof pr);
        memset(to, 0, sizeof to);
        es = 2;

        int cnt = 0;
        for (int i = 0; i < n; i++) {
            int h;
            scanf("%d", &h);

            for (int j = 0; j < h; j++) {
                scanf("%d", to+es);
                nx[es] = hd[i]; hd[i] = es; es++;
                if (to[nx[es]] == to[es])
                    pr[es] = pr[nx[es]];
                else
                    pr[es] = nx[es];
                cnt++;
            }
        }

        int att = n;
        /*
        for (int i = 1; i < n; i++) {
            if (to[hd[i]] == to[hd[att]]) {
                if ((!nx[hd[att]]) || (nx[hd[i]] && to[nx[hd[i]]] > to[nx[hd[att]]]))
                    att = i;
            } else if (to[hd[i]] > to[hd[att]]) {
                att = i;
            }
        }
        */
        
        int res = -1;
        while (cnt) {
            int maxi = att;

            for (int i = 0; i < n; i++) {
                if (cmp(maxi, i, att))
                    maxi = i;
            }
            DEBUG("%d(%d)", maxi, to[hd[maxi]]);

            if (maxi != att) {
                res++;
                DEBUG("+");
                if (hd[att]) {
                    res++;
                    DEBUG("+");
                }
            }
            DEBUG("\n");
            hd[maxi] = nx[hd[maxi]];
            att = maxi;
            cnt--;
        }

        printf("Case %d: %d\n", ++turn, res);
    }
}
