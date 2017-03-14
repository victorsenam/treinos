#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

const int N = 2003;
const int M = 200003;

struct hsh {
    num h1, h2;
    hsh operator ^ (const hsh & b) const {
        hsh n;
        n.h1 = (h1^(b.h1));
        n.h2 = (h2^(b.h2));
        return n;
    }
    bool operator < (const hsh & b) const {
        if (h1 == b.h1)
            return h2 < b.h2;
        return h1 < b.h1;
    }
    bool operator == (const hsh & b) const {
        return (h1==b.h1)&&(h2==b.h2);
    }
};

int n, m;
int hd[N], nx[M], to[M], es;
hsh ch[N], vl[M];
int a, b;
int visi[N];
int rets[M], rs;
int low[N];
int pre[N];
int ord;
int brid;

hsh dfs (int u, int fr) {
    if (visi[u] == 1) {
        rets[rs++] = fr;
        hsh aux;
        aux.h1 = rand();
        aux.h1 <<= 32;
        aux.h1 |= rand();
        aux.h2 = rand();
        aux.h2 <<= 32;
        aux.h2 |= rand();

        ch[u] = (ch[u]^aux);
        return aux;
    }
    if (visi[u] == 2) {
        hsh aux;
        aux.h1 = aux.h2 = 0;
        return aux;
    }

    pre[u] = low[u] = ord++;
    visi[u] = 1;

    hsh ret;
    ret.h1 = ret.h2 = 0;
    for (int ed = hd[u]; ed != -1; ed = nx[ed]) {
        if (ed != (fr^1)) {
            int aux = visi[to[ed]];
    //        printf("[%d] (%d,%d) (%d)\n", ed, u, to[ed], visi[to[ed]]);
            vl[ed] = dfs(to[ed], ed);
            low[u] = min(low[u], low[to[ed]]);
            ret = (ret^vl[ed]);
        }
    }

    if (low[u] == pre[u] && fr >= 0) {
        brid++;
     //   printf("%d is bridge\n", fr);
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
    //for (int i = 0; i < rs; i++)
        //printf("%d has val %llu\n", rets[i], vl[rets[i]]);

    int res = brid*(m-1) - brid*(brid-1)/2;

    int qtd = 0;
    hsh last;
    last.h1 = last.h2 = 0;
    int sz = 0;

    //for (int i = 0; i < m; i++)
    //    printf("%02d %s\n", i+1, ((bitset<8>)(vl[2*i]|vl[2*i+1])).to_string().c_str());

    for (int i = 0; i < 2*m; i++) {
        if (vl[i] == last)
            continue;
        vl[sz++] = vl[i];
    }

    sort(vl, vl+sz);
    for (int i = 0; i < sz; i++) {
        if (vl[i].h1 == 0 && vl[i].h2 == 0)
            continue;
        if (last == vl[i]) {
            qtd++;
        } else {
            res += qtd*(qtd-1)/2;
 //           printf("sz %d\n", qtd);
            qtd = 1;
            last = vl[i];
        }
    }
    res += qtd*(qtd-1)/2;
  //  printf("sz %d\n", qtd);

    printf("%d\n", res);
    
}
