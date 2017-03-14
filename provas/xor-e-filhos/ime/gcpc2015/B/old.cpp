#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 1007;
int n, k, a;
int hd[N], to[N*N], nx[N*N], es;
int cnt;
bool rem[N];
int siz[N];
int visi[N], turn;

int dfs (int u) {
    if (u == -1 ||rem[u])
        return 0;
    if (visi[u] == turn)
        return siz[u];
    visi[u] = turn;
    siz[u] = 1;
    for (int ed = hd[u]; ed; ed = nx[ed])
        siz[u] = max(dfs(to[ed])+1, siz[u]);
    return siz[u];
}

void eras (int u) {
    if (u == -1 ||rem[u])
        return;
    rem[u] = 1;
    cnt++;

    int maxi = -1;
    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if (dfs(to[ed]) > dfs(maxi))
            maxi = to[ed];
    }

    eras(maxi);
}

int main () {
    scanf("%d", &n);

    es = 2;
    for (int i = 0; i < n; i++) {
        scanf("%d", &k);
        for (int j = 0; j < k; j++) {
            scanf("%d", &a);

            nx[es] = hd[i]; to[es] = a; hd[i] = es++;
        }
    }

    cnt = 0;

    while (cnt < n) {
        fflush(stderr);
        turn++;
        int maxi = -1;
        for (int i = 0; i < n; i++) {
            if (dfs(i) > dfs(maxi))
                maxi = i;
        }

        eras(maxi);
    }
    printf("%d\n", turn);
}
