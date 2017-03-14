#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 60;
const int M = 50000;
int n;
int hd[N], nx[M], to[M], pr[M], es;

bool cmp_2 (int i, int j) {
    if (i == j) return 1;
    if (to[i] == to[j]) return cmp_2(pr[i], pr[j]);
    return to[i] <= to[j];
}

inline bool cmp (int i, int j, int mx) {
    if (i == j) return 1;
    if (to[hd[i]] == to[hd[j]]) {
        if (i == mx) return 1;
        if (j == mx) return 0;
      return cmp_2(pr[hd[i]], pr[hd[j]]);
    return (to[nx[hd[i]]] <= to[nx[hd[j]]]);
}
return to[hd[i]] > to[hd[j]];
}

int main () {
int turn = 0;
while (scanf("%d", &n) != EOF) {
    memset(hd, 0, sizeof hd);
    memset(nx, 0, sizeof nx);
    memset(to, 0, sizeof to);
    memset(pr, 0, sizeof pr);
    es = 2;

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int h;
        scanf("%d", &h);
    //    DEBUG("stack %d\n", i);
        for (int j = 0; j < h; j++) {
            scanf("%d", to+es);
            nx[es] = hd[i]; hd[i] = es;
            if (to[nx[es]] == to[es])
                pr[es] = pr[nx[es]];
            else
                pr[es] = nx[es];

  //          DEBUG("%d(%d)->%d(%d)\n", es, to[es], pr[es], to[pr[es]]);
            cnt++;
            es++;
        }
    }

    int att = n;
    
    int res = -1;
    while (cnt) {
        int maxi = att;

        for (int i = 0; i < n; i++)
            if (!cmp(maxi, i, att))
                maxi = i;

        if (maxi != att) {
            res++;
            if (hd[att])
                res++;
        }

        DEBUG("%d -> %d\n", maxi, res);
        hd[maxi] = nx[hd[maxi]];
        att = maxi;
        cnt--;
    }

    printf("Case %d: %d\n", ++turn, res);
}
}
