#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 107;
const int M = 2*N;

int n;
int hd[N], to[M], nx[M], pr[M], es;
int cs[N], nd[N], aux;
int rm[M];
int vs[M], turn;

int dfs (int fr) {
    if (vs[fr] == turn)
        return rm[fr];
    vs[fr] = turn;

    int u = to[fr];
    rm[fr] = 0;
    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if ((fr|1) == (ed|1)) continue;
        rm[fr] += dfs(to[ed]);
    }

    return rm[fr];
}

int main () {
    while (scanf("%d", &n) && n) {
        ++turn;
        es = 2;
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", nd+i, &aux, cs+i);
            cs[i] += aux;
        }

        for (int i = 1; i < n; i++) {
            scanf("%d %d", to+es, to+es+1);
            to[es]--; to[es+1]--;
            nx[es] = hd[to[es^1]]; hd[to[es^1]] = es; pr[es] = 0; pr[nx[es]] = es; es++;
            nx[es] = hd[to[es^1]]; hd[to[es^1]] = es; pr[es] = 0; pr[nx[es]] = es; es++;
        }

        for (int i = 0; i < es; i++)
            dfs(es);

        for (int i = 0; i < n; i++) {
            int lim = hd[i];
            while (nx[lim]) lim = nx[lim];
            while (lim != hd[i]) {
                for (int ed = hd[i]; ed != lim; ed = nx[ed]) {
                    if (rm[ed] > rm[nx[ed]]) {
                        aux = nx[ed];
                        nx[ed] = nx[aux];
                        nx[aux] = ed;
                        pr[aux] = pr[ed];
                        pr[ed] = aux;
                    }
                }
                lim = pr[lim];
            }
            printf("%d:", i+1);
            for (int ed = hd[i]; ed; ed = nx[ed])
                printf(" %d", to[ed]+1);
            printf("\n");
        }
    }
}
