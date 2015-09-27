#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

int uf[N];
int wh[N];
int edge[N][2];
bool use[N];
int r[N];
int rs;
int res;
int n, m, a, b, q;
int qs[N];

int find (int i ) {
    if (uf[i] == i)
        return i;
    return (uf[i] = find(uf[i]));
}

void join (int i, int j) {
    i = find(i);
    j = find(j);
    if (i == j)
        return;
    res--;
    if (wh[i] < wh[j])
        swap(i,j);
    wh[j] += wh[i];
    uf[i] = j;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++){
        uf[i] = i;
        wh[i] = 1;
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        edge[i][0] = a;
        edge[i][1] = b;
    }

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d", &a);
        a--;
        use[a] = 1;
        qs[i] = a;
    }

    res = n;
    for (int i = 0; i < m; i++) {
        if (use[i])
            continue;
        join(edge[i][0], edge[i][1]);
    }

    for (int i = q-1; i >= 0; i--) {
        r[i] = res;
        join(edge[qs[i]][0], edge[qs[i]][1]);
    }

    for (int i = 0; i < q; i++) {
        if (i)
            printf(" ");
        printf("%d", r[i]);
    }
    printf("\n");
}
