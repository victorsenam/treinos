#include <bits/stdc++.h>

using namespace std;

const int N = 1007;
const int M = 100007;

int hd[N], nx[M], to[M];
int n, m;
int uf[N], wf[N];
int ed[M];
int a[M], b[M], w[M];
bool ty[M];
int p, x;

int find (int a) {
    if (uf[a] == a)
        return a;
    return (uf[a] = find(uf[a]));
}

void join (int i, int j) {
    i = find(i);
    j = find(j);
    if (i == j)
        return;
    if (wf[i] > wf[j])
        swap(i,j);
    wf[j] += wf[i];
    uf[i] = j;
}

bool cmp (int i, int j) {
    int ta = (ty[a[i]]|ty[b[i]]);
    int tb = (ty[a[j]]|ty[b[j]]);
    if (ta == tb)
        return w[i] < w[j];
    return ta < tb;
}

int main () {
    while (scanf("%d %d %d", &n, &m, &p) != EOF) {
        for (int i = 0; i < n; i++) {
            uf[i] = i;
            ty[i] = 0;
            wf[i] = 1;
        }
        
        for (int i = 0; i < p; i++) {
            scanf("%d", &x);
            ty[x-1] = 1;
        }
        int maxi = -1;
        for (int i = 0; i < n; i++) {
            if (!ty[i])
                maxi = max(maxi, i);
        }
        
        int sum = 0;
        int sl = 0;
        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", a+i, b+i, w+i);
            a[i]--; b[i]--;
            if (a[i] == b[i]) {
                sl++;
            } else {
                sum += w[i];
            }
            ed[i] = i;
        }

        if (p == n) {
            if (m != n*(n-1)/2 + sl) {
                printf("impossible\n");
            } else {
                printf("%d\n", sum);
            }
            continue;
        }

        sort(ed, ed+m, cmp);

        int res = 0;
        bool ok = 0;
        for (int i = 0; maxi >= 0 && i < m; i++) {
            int u, v;
            u = a[ed[i]];
            v = b[ed[i]];
            if (ty[u]|ty[v])
                if (wf[find(maxi)] < n-p)
                    break;
            if (ty[u]&ty[v])
                continue;
            if (find(u) != find(v)) {
                join(u, v);
                res += w[ed[i]];
            }
        }
        
        if (maxi < 0 || wf[find(maxi)] < n)
            printf("impossible\n");
        else
            printf("%d\n", res);
    }
}
