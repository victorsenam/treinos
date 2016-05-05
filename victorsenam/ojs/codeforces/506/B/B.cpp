#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;
const int M = 400007;

int hd[N], nx[M], to[M], es;
int visi[N];
bool loop;
int uf[N], wf[N], lp[N];
int n, m;

int find (int i) {
    if (i == uf[i]) return i;
    return uf[i] = find(uf[i]);
}

void join (int i, int j) {
    if ( (i = find(i)) == (j = find(j)) ) return;
    if (wf[i] < wf[j]) swap(i, j);
    wf[i] += wf[j];
    uf[j] = i;
}


bool dfs (int i) {
    if (visi[i])
        return (visi[i] == 1);
    visi[i] = 1;

    int res = 0;
    for (int ed = hd[i]; ed; ed = nx[ed])
        res |= dfs(to[ed]);
    visi[i] = 2;
    return res;
    }

int main () {
    scanf("%d %d", &n, &m);
    es = 2;
    for( int i = 0; i < n; i++) {
        uf[i] = i;
        wf[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        join(a, b);
        nx[es] = hd[a]; to[es] = b; hd[a] = es++;
    }
    
    int res = 0;
    for (int i = 0; i < n; i++)
        lp[find(i)] |= dfs(i);
    
    for (int i = 0; i < n; i++)
        if (i == find(i)) 
            res += wf[i] + lp[i] - 1;

    printf("%d\n", res);
}
