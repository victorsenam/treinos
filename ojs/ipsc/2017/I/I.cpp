#include <bits/stdc++.h>
#define debug if (0)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;
const int M = 3e6;

int t, n, m;
int hd[N], to[M], nx[M], es;
int st[N], ss, cs;
int pre[N], low[N], vs[N], os;
int mrk[N];
int cm[N];
int ach[N];
int vv[N][3], tr;
int fff[N];
vector<int> com[N];

int go (int u, int w, int ps, int l = 0) {
    if (l) tr++;
    if (u==w) ps++;
    if (ps > 2) return 0;

    if (vv[u][ps] == tr)
        return 0;
    vv[u][ps] = tr;
    
    int res = 0;
    if (u == n-1) {
        if (ps == 0) res = 1;
        else if (ps == 1) res = 0;
        else res = 2;
    }

    for (int ed = hd[u]; ed; ed = nx[ed]) {
        res = max(res, go(to[ed], w, ps));
    }

    return res;
}

int dfs (int fr) {
    int u = to[fr];
    if (vs[u] == 1)
        return pre[u];
    if (vs[u] == 2)
        return INT_MAX;

    vs[u] = 1;
    pre[u] = low[u] = os++;
    st[ss++] = u;

    for (int ed = hd[u]; ed; ed = nx[ed])
        low[u] = min(dfs(ed), low[u]);

    if (pre[u] == low[u]) {
        while (ss && pre[st[ss-1]] >= low[u]) {
            vs[st[ss-1]] = 2;
            com[cs].push_back(st[ss-1]);
            cm[st[--ss]] = cs;
        }
        cs++;
    }

    return low[u];
}

void printgraph () {
    cout << n << " " << m << endl;
    for (int i = 0; i < n; i++) {
        for (int ed = hd[i]; ed; ed = nx[ed])
            cout << to[ed]+1 << " ";
        cout << endl;
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> t;

    while (t--) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            pre[i] = low[i] = -1;
            ach[i] =  0;
            fff[i] = 0;
            vs[i] = 0;
            hd[i] = 0;
            mrk[i] = 0;
            com[i].clear();
        }
        es = 2;
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            if (a == b)
                mrk[a] = 1;
            to[es] = b; nx[es] = hd[a]; hd[a] = es++;
        }

        cs = os = ss = 0;
        to[0] = 0;
        dfs(0);

        for (int i = 0; i < cs; i++) {
            debug cout << "component " << i << ":";
            if (cm[n-1] == i)
                ach[i] = 1;
            for (int u : com[i]) {
                debug cout << " " << u + 1;
                for (int ed = hd[u]; !ach[i] && ed; ed = nx[ed])
                    if (ach[cm[to[ed]]])
                        ach[i] = 1;
            }

            if (ach[i])
                debug cout << " achieves";
            debug cout << endl;
        }

        set<int> s;
        vector<int> res;
        for (int i = cs-1; i >= 0; i--) {
            s.erase(i);
            if (!ach[i]) continue;
            if (s.empty() && com[i].size() == 1 && !mrk[com[i][0]]) {
                res.push_back(com[i][0]);
                fff[com[i][0]] = 1;
            }
            for (int u : com[i]) {
                for (int ed = hd[u]; ed; ed = nx[ed]) {
                    if (cm[to[ed]] < i && ach[cm[to[ed]]])
                        s.insert(cm[to[ed]]);
                }
            }
        }
        
        if (false && go(0,-1,0,1)) {
            for (int i = 0; i < n; i++) {
                int r = go(0,i,0,1);

                if ((fff[i] == 1)^(r == 0)) {
                    cout << i+1 << " is wrong " << fff[i] << " " << r << endl;
                    printgraph();
                    return 0;
                }
            }
        }

        cout << res.size() << endl;
        for (int i = 0; i < res.size(); i++) {
            if (i)
                cout << " ";
            cout << res[i] + 1;
        }
        cout << endl;
    }
}
