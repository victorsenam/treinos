#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 2e5+7;
const int M = 30;

int n, m, q;
int uf[N], wf[N];
char str[2][M];

map<string, int> mp;

int find (int u) {
    if (u == uf[u]) return u;
    return uf[u] = find(uf[u]);
}

void join (int u, int v) {
    if ((u = find(u)) == (v = find(v))) return;
    if (wf[u] > wf[v]) swap(u,v);
    wf[v] += wf[u];
    uf[u] = v;
}

int main () {
    scanf("%d %d %d", &n, &m, &q);

    for (int i = 0; i < n; i++) {
        scanf(" %s", str[0]);
        mp[str[0]] = 2*i;
    }

    for (int i = 0; i < 2*n; i++) {
        uf[i] = i; wf[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);

        scanf(" %s %s", str[0], str[1]);

        int a = mp[str[0]], b = mp[str[1]];

        if (x == 1) {
            if (find(a) == find(b+1)) printf("NO\n");
            else {
                printf("YES\n");
                join(a,b);
                join(a+1,b+1);
            }
        } else {
            if (find(a) == find(b)) printf("NO\n");
            else {
                printf("YES\n");
                join(a,b+1);
                join(a+1,b);
            }
        }
    }

    for (int i = 0; i < q; i++) {
        scanf(" %s %s", str[0], str[1]);
        int a = mp[str[0]], b = mp[str[1]];

        if (find(a) == find(b))
            printf("1\n");
        else if (find(a+1) == find(b))
            printf("2\n");
        else
            printf("3\n");
    }
}

