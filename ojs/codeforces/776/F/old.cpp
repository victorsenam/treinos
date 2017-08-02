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

const int N = 3e5+7;

stack<int> st;
int n, m;
int v[N][2];
vector<int> df[N], imp[N];

int vtx[N];
int rs[N], p[N];
int hd[N], to[2*N], nx[2*N], es;
int pr[N];
int siz[N];
int visi[N], turn;

int dfs (int u, int fr) {
    if (visi[u] == turn) return 0;
    visi[u] = turn;
    pr[u] = fr;
    siz[u] = 1;
    
    for (int ed = hd[u]; ed; ed = nx[ed])
        if (to[ed] != fr && !rs[to[ed]])
            siz[u] += dfs(to[ed], u);
    
    return siz[u];
}

void build (int u, int depth, int fr) {
    turn++;
    int size = dfs(u, fr);

    int ed = -1;
    while (ed) {
        for (ed = hd[u]; ed && (pr[u] == to[ed] || rs[to[ed]] || siz[to[ed]] + siz[to[ed]] <= size); ed = nx[ed]);
        if (ed) u = to[ed];
    }

    //debug("centroid: %d\n", u);
    rs[u] = depth;
    
    for (ed = hd[u]; ed; ed = nx[ed])
        if (to[ed] != fr && !rs[to[ed]])
            build(to[ed], depth+1, u);
}

int main () {
    scanf("%d %d", &n, &m);
    
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &v[i][0], &v[i][1]);
        v[i][0]--; v[i][1]--;
        sort(v[i], v[i]+2);
    }

    for (int i = 0; i < m; i++)
        p[i] = i+1;

    sort(p, p+m, [] (int i, int j) {
        if (v[i][0] != v[j][0])
            return v[i][0] < v[j][0];
        return v[i][1] > v[j][1];
    });

    es = 2;
    st.push(0);

    int l = 0;
    for (int _i = 0; _i < m || st.top(); _i++) {
        int i = p[_i];

        int u = st.top();
        int r = l;

        if (_i >= m || (u && v[u][1] <= v[i][0])) {
            //debug("rem %d(%d,%d)\n", u, v[u][0], v[u][1]);
            r = v[u][1];
            st.pop();
            _i--;
        } else {
            r = v[i][0];
            st.push(i);
            //debug("add %d(%d,%d)\n", i, v[i][0], v[i][1]);
        }

        int v = st.top();
        
        while (l < r)
            imp[u].push_back(l++);
        imp[u].push_back(l);

        to[es] = v; nx[es] = hd[u]; hd[u] = es++;
        debug("adj %d %d\n", u, v);
    }
    while (l < n)
        imp[0].push_back(l++);

    assert(st.top() == 0);

    for (int i = 0; i <= m; i++) {
        p[i] = i;
        auto it = unique(imp[i].begin(), imp[i].end());
        imp[i].resize(distance(imp[i].begin(), it));

/*
        printf("%d:", i);
        for (int j : imp[i])
            printf(" %d", j+1);
        printf("\n");
*/
    }

    sort(p, p+m+1, [] (int i, int j) {
        int a = imp[i].size(), b = imp[j].size();

        while (a && b) {
            a--; b--;
            if (imp[i][a] == imp[j][b]) continue;
            return imp[i][a] < imp[j][b];
        }

        if (!b) return false;
        return true;
    });

    build(0, 1, -1);
    for (int i = 0; i <= m; i++) {
        debug("[%d]", p[i]);
        printf("%d ", rs[p[i]]);
    }
    printf("\n");
}
