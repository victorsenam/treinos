#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef double db;

const int N = 1e3+7;
const int M = 1e5+7;

int a, b;
int n, m, k;
int uf[N], wf[N], sp[N];

int find (int i) {
    if (uf[i] == i) return i;
    return uf[i] = find(uf[i]);
}

int join (int i, int j) {
    i = find(i);
    j = find(j);
    if (i == j || sp[i] && sp[j]) return 0;
    if (wf[i] < wf[j]) swap(i,j);
    wf[i] += wf[j];
    sp[i] |= sp[j];
    uf[j] = uf[i];
    return 1;
}

int main () {
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < n; i++) {
        uf[i] = i;
        wf[i] = 1;
        sp[i] = 0;
    }
    
    for (int i = 0; i < k; i++) {
        int c;
        scanf("%d", &c);
        c--;
        sp[c] = 1;
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        join(a, b);
    }
    int res = -m;
    int mr = -1;
    for (int i = 0; i < n; i++) {
        if (find(i) == i && sp[i])
            if (mr == -1 || wf[mr] < wf[i])
                mr = i;
    }
    
    if (mr == -1) {
        for (int i = 1; i < n; i++)
            join(i, i-1);
    } else {
        for (int i = 0; i < n; i++)
            if (find(i) == i && !sp[i])
                join(i, mr);
    }

    for (int i = 0; i < n; i++)
        if (find(i) == i)
            res += wf[i]*(wf[i]-1)/2;

    printf("%d\n", res);
}
