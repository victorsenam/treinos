#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

const int N = 2003;
const int M = 200003;

int n, m;
int hd[N], nx[M], to[M], es;
num ch[N], vl[M];
int a, b;
int visi[N];
int rets[M], rs;

num dfs (int u, int fr) {
    printf("%d\n", u);
    if (visi[u] == 1) {
        rets[rs++] = fr;
        num aux = rand();
        aux <<= 32;
        aux |= rand();
        ch[u] ^= aux;
        printf("ret %d %d -> %s\n", to[fr^1], to[fr], ((bitset<64>)aux).to_string().c_str());
        return aux;
    }
    if (visi[u] == 2)
        return 0;

    visi[u] = 1;

    num ret = 0;
    for (int ed = hd[u]; ed != -1; ed = nx[ed]) {
        printf("%d -> %d\n", u, to[ed]);
        if (ed != fr^1) {
            vl[ed] = dfs(to[ed], ed);
            ret ^= vl[ed];
        }
    }

    visi[u] = 2;
    return ret^ch[u];
}

int main () {
    srand(time(NULL)); rand(); rand();
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
        hd[i] = -1;
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        nx[es] = hd[a]; hd[a] = es; to[es] = b; es++;
        nx[es] = hd[b]; hd[b] = es; to[es] = a; es++;
    }

    for (int i = 0; i < n; i++)
        dfs(i, -1);

    for (int i = 0; i < 2*m; i++) {
        printf("%d %d: %s\n", to[i^1], to[i], ((bitset<64>)vl[i]).to_string().c_str() );
    }
}
