#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 3e5+7;

stack<int> st;
int n, m;
int v[N][2];
vector<int> df[N];

int vtx[N];
int rs[N], imp[N], p[N];
int hd[N], to[2*N], nx[2*N], es;
int pr[N];
int siz[N];

int dfs (int u, int fr) {
    pr[u] = fr;
    siz[u] = 1;
    
    for (int ed = hd[u]; ed; ed = nx[ed])
        if (to[ed] != fr)
            siz[u] += dfs(to[ed], u);
    
    return siz[u];
}

void build (int u, int depth, int fr) {
    int size = dfs(u, fr);

    int ed = -1;
    while (ed) {
        for (ed = hd[u]; ed && (pr[u] == to[ed] || siz[to[ed]] + siz[to[ed]] <= size); ed = nx[ed]);
        if (ed) u = to[ed];
    }

    //debug("centroid: %d\n", u);
    rs[u] = depth;
    
    for (ed = hd[u]; ed; ed = nx[ed])
        if (to[ed] != fr)
            build(to[ed], depth+1, u);
}

int main () {
    scanf("%d %d", &n, &m);
    
    int mn = n;

    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &v[i][0], &v[i][1]);
        v[i][0]--; v[i][1]--;
        sort(v[i], v[i]+2);
        mn = min(mn, v[i][0]);
        df[v[i][0]].push_back(i);
        df[v[i][1]].push_back(i);
    }

    for (int i = 0; i < n; i++)
        sort(df[i].begin(), df[i].end());

    es = 2;
    st.push(0);
    for (int i = 0; i < n; i++) {
        //debug("vert %d\n", i);
        int ini = st.top();
        imp[ini] = i; // durante o contest isso tava antes do for

        for (int jj = df[i].size()-1; jj >= 0; jj--) {
            int j = df[i][jj];
            //debug("%d[%d,%d]\n", j, v[j][0], v[j][1]);

            if (st.top() == j)
                st.pop();
            else
                st.push(j);

            imp[st.top()] = i;
        }
        if (ini == st.top() || !i) continue;
        nx[es] = hd[ini]; to[es] = st.top(); hd[ini] = es++;
        nx[es] = hd[st.top()]; to[es] = ini; hd[st.top()] = es++;
        //debug("are adj %d %d\n", ini, st.top());
    }

    //assert(st.top() == 0);

    for (int i = 0; i <= m; i++)
        p[i] = i;
    sort(p, p+m+1, [] (int i, int j) {
        return imp[i] < imp[j];
    });

    build(0, 1, -1);
    for (int i = 0; i <= m; i++)
        printf("%d ", rs[p[i]]);
    printf("\n");
}
