#include <bits/stdc++.h>

using namespace std;

const int N = 101;
const int M = 1001;
const int L = 10001;

int n, m;
int a, b;
int es;
int to[3*N*M], nx[3*N*M], head[L];

void dfs (int u, int l) {
    int nw = es;
    nx[es] = nx[l];
    nx[l] = es;
    to[es++] = u;

    for (int ed = head[u]; ed != -1; ed = head[u]) {
        head[u] = nx[ed];
        dfs(to[ed], nw);
    }
}

int main () {
    scanf("%d", &n);

    memset(head, -1, sizeof head);

    for (int i = 0; i < n; i++) {
        scanf("%d", &m);
        scanf("%d", &a);
        
        for (int i = 0; i < m; i++) {
            scanf("%d", &b);

            nx[es] = head[a];
            head[a] = es;
            to[es++] = b;
            swap(a, b);
        }
    }

    head[0] = es;
    nx[es] = -1;
    to[es++] = a;

    dfs(a, es-1);

    printf("%d ", es-head[0]-2);
    for (int ed = nx[head[0]]; ed != -1; ed = nx[ed]) 
        printf("%d ", to[ed]);
    printf("\n");
}
