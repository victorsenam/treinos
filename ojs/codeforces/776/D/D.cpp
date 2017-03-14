#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e6+7;

int n, m;
int r[N];
int v[N][2];
int hd[N], to[2*N], nx[2*N], es;
int pre[N], ret[N], os, ts;
int visi[N], turn;
int st[N], ss;
int comp[N], cs;

int dfs (int u) {
    if (visi[u] == turn)
        return pre[u];
    if (visi[u] == turn+1)
        return INT_MAX;

    visi[u] = turn;
    pre[u] = ret[u] = os++;
    st[ss++] = u;

    for (int ed = hd[u]; ed; ed = nx[ed])
        ret[u] = min(dfs(to[ed]), ret[u]);
    visi[u] = turn+1;

    if (pre[u] == ret[u]) {
        while (ss && pre[st[ss-1]] >= ret[u])
            comp[st[--ss]] = cs;
        cs++;
    }

    return ret[u];
}

void addor (int x, int y) {
    nx[es] = hd[x^1]; to[es] = y; hd[x^1] = es++;
    nx[es] = hd[y^1]; to[es] = x; hd[y^1] = es++;
}

int main () {
    scanf("%d %d", &n, &m);
    turn = 1;

    for (int i = 0; i < n; i++)
        scanf("%d", &r[i]);

    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);
        for (int j = 0; j < x; j++) {
            int a;
            scanf("%d", &a);
            a--;

            swap(v[a][0], v[a][1]);
            v[a][0] = i;
        }
    }

    es = 2;
    for (int i = 0; i < n; i++) {
        if (!r[i]) {
            addor(2*v[i][0], 2*v[i][1]);
            addor(2*v[i][0]+1, 2*v[i][1]+1);

            //debug("(%d ^ %d)\n", v[i][0], v[i][1]);
        } else {
            addor(2*v[i][0]+1, 2*v[i][1]);
            addor(2*v[i][0], 2*v[i][1]+1);

            //debug("!(%d ^ %d)\n", v[i][0], v[i][1]);
        }
    }

    for (int i = 0; i < 2*m; i++)
        dfs(i);

    for (int i = 0; i < 2*m; i+=2) {
        if (comp[i] == comp[i+1]) {
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
}
