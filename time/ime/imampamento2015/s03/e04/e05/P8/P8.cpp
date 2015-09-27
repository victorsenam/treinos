#include <bits/stdc++.h>

using namespace std;

const int N = 207;
const int M = 207;

vector<int> adj[N];
map<string, int> mp;
int seen[N];
int n, m, a, b;
int memo[N][M][N];
int pre[N], hei[N], deg[N];
char c, temp[109];

int dfs(int v) {
    if (seen[v]) return hei[v];
    seen[v] = 1;
    hei[v] = 1;

    for (int i = 0; i < adj[v].size(); i++)
        hei[v] += dfs(adj[v][i]);
    return hei[v];
}

int pd(int v, int m, int c) {
    if (m == 0) return 0;
    if (adj[v].size() == c) return pre[v];

    int & me = memo[v][m][c];

    if (me != -1)
        return me;

    me = INT_MAX;

    for (int i =0 ; i <= min(m,hei[adj[v][c]]); i++) {
        int lf = pd(adj[v][c], i, 0);
        int rf = pd(v, m-i, c+1);
        int res = max(lf, rf);
        if (res != INT_MAX)
            res = lf+rf;
        me = min(res, me);
    }

 //   printf("%d %d %d -> %d\n", v, m, c, me);
    return me;
}

int main () {
    while(scanf("%d %d", &n, &m) != EOF) {
        mp.clear();
        for (int i = 0; i <= n; i++) {
            adj[i].clear();
            deg[i] = 0;
            seen[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            scanf(" %s", temp);
            if (mp.find(temp) != mp.end()) {
                a = mp.find(temp)->second;               
            } else {
                a = mp.size();
                mp.insert(make_pair((string)temp, a));
            }
            scanf("%d", pre+a+1);
            
            while (42) {
                scanf("%c", &c);
                if (c == ' ') continue;
                if (c == '\n' || c == '\0') break;
                
                ungetc(c, stdin);
                scanf("%s", temp);
                
                if (mp.find(temp) != mp.end()) {
                    b = mp.find(temp)->second;
                } else {
                    b = mp.size();
                    mp.insert(make_pair((string) temp, b));
                }
                adj[a+1].push_back(b+1);
                deg[b+1]++;
            }
        }

        for (int i = 1; i <= n; i++)
            if (deg[i] == 0)
                adj[0].push_back(i);

        
        for (int i = 0; i <= n; i++) {
 //           printf("%d(%d) ", i, pre[i]);
            for (int k = 0; k < adj[i].size(); k++) {
//                printf("%d ", adj[i][k]);
                for (int j = 0; j <= m; j++)
                    memo[i][j][k] = -1;
            }
  //          printf("\n");
        }

        dfs(0);
        pre[0] = INT_MAX;

        printf("%d\n", pd(0, m, 0));
        scanf(" %c", &c);
        if (c == '#') break;
        else ungetc(c, stdin);
    }

}
