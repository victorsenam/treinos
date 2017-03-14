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

const int N = 2000007;

int n, m;
int mat[N];
int ord[N], deg[N];
int hd[N], nx[N], to[N], es;
int uf[N], wf[N], val[N];
int qu[N], qi, qf;

int cmp_t (int i, int j)
{ return mat[i] < mat[j]; }

int find (int i) {
    if (uf[i] == i)
        return i;
    return uf[i] = find(uf[i]);
}

void join(int i, int j) {
    i = find(i); j = find(j);
    if (i == j) return;
    if (wf[i] < wf[j]) swap(i, j);
    wf[i] += wf[j];
    uf[j] = i;
}

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n*m; i++) {
        scanf("%d", &mat[i]);
        uf[i] = i;
        wf[i] = 1;
        hd[i] = 0;
    }
    es = 2;

    int acc = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            ord[acc+j] = j + i*m;
        sort(ord+acc,ord+acc+m,cmp_t);

        for (int j = 1; j < m; j++)
            if (mat[ord[acc+j]] == mat[ord[acc+j-1]])
                join(ord[acc+j], ord[acc+j-1]);
        acc += m;
    }
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++)
            ord[acc+i] = i*m + j;
        sort(ord+acc,ord+acc+n,cmp_t);

        for (int i = 1; i < n; i++)
            if (mat[ord[acc+i]] == mat[ord[acc+i-1]])
                join(ord[acc+i], ord[acc+i-1]);
        acc += n;
    }
    
    acc = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (mat[ord[acc+j]] == mat[ord[acc+j-1]])
                continue;

            int a = find(ord[acc+j-1]); int b = find(ord[acc+j]);

            deg[b]++;
            nx[es] = hd[a]; hd[a] = es; to[es] = b; es++;
        }
        acc += m;
    }
    for (int j = 0; j < m; j++) {
        for (int i = 1; i < n; i++) {
            if (mat[ord[acc+i]] == mat[ord[acc+i-1]])
                continue;

            int a = find(ord[acc+i-1]); int b = find(ord[acc+i]);
            deg[b]++;
            nx[es] = hd[a]; hd[a] = es; to[es] = b; es++;
        }
        acc += n;
    }

    for (int i = 0; i < n*m; i++) {
        if (deg[find(i)] == 0 && val[find(i)] == 0) {
            val[find(i)] = 1;
            qu[qf++] = find(i);
        }
    }

    while (qi < qf) {
        int u = qu[qi++];

        for (int ed = hd[u]; ed; ed = nx[ed]) {
            int a = to[ed];
            deg[a]--;

            if (deg[a] == 0) {
                val[a] = val[u]+1;
                qu[qf++] = a;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int  j = 0; j < m; j++) {
            printf("%d ", val[find(i*m+j)]);
        }
        printf("\n");
    }
}
