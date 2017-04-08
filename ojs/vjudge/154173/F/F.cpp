#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 3e5 + 7;

int uf[N], wf[N];
int v[N][4];
int n;
int g;
int t;

int find (int u) {
    if (u == uf[u]) return u;
    return uf[u] = find(uf[u]);
}

void join (int u, int v) {
    if ((u = find(u)) == (v = find(v))) return;
    if (wf[v] < wf[u]) swap(u,v);
    wf[v] += wf[u];
    uf[u] = v;
}

int main () {
    scanf("%d", &t);
    while (t--) {
        int g;
        scanf("%d %d", &n, &g);
        g--;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 4; j++) {
                scanf("%d", &v[i][j]);
                v[i][j]--;
            }
            uf[i] = i;
            uf[i+n] = i+n;
            wf[i] = wf[i+n] = 1;
        }

        join(g, g+n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 4; j++) {
                if (v[i][j] < i) {
                    for (int k = 0; k < 4; k++) {
                        if (v[v[i][j]][k] == i) {
                            join(i+((j&1)*n), v[i][j]+((k&1)*n));
                        }
                    }
                }
            }
        }

        int cnt = -1;
        for (int i = 0; i < 2*n; i++)
            cnt += (uf[i] == i);
        printf("%d\n", cnt);
    }
}
