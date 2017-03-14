#include <bits/stdc++.h>

using namespace std;

#define N 500

typedef int num;

int pre[N*N*4+1];
int ret[N*N*4+1];
int cmp[N*N*4+1];
int mat[N*N];
stack<int> st;
vector<int> adj[N*N*4+1];
int blccnt, whtcnt, cmpcnt, cnt;
int n, m;
int src, dst;
char at;
int dl[12] = {0, 1, 0, -1, 0, 2, 0, -2, 1, 1, -1, -1};
int dc[12] = {1, 0, -1, 0, 2, 0, -2, 0, 1, -1, -1, 1};

int isBlk (int i, int j) {
    if (i < 0 || i >= n) return 0;
    if (j < 0 || j >= m) return 0;
    return mat[i*m+j] + 1;
    // -1 w
    // 0 .
    // 1 b
}

bool isStrong (int v) {
    while (!st.empty()) {
        dst = st.top();
        st.pop();

 //       printf("%d ", dst);

        cmp[dst] = cmpcnt;
        if (cmp[(dst/4)*4 + (dst+2)%4] == cmpcnt) return 0;
        if (dst == v) break;
    }
 //   printf("\n");
    cmpcnt++;

    return 1;
}

int dfs (int v) {
    if (pre[v] != -1) return 1;
    //printf("- %d -\n", v);

    st.push(v);
    pre[v] = ret[v] = cnt++;

    for (int i = 0; i < adj[v].size(); i++) {
        if (pre[adj[v][i]] == -1) {
            if (!dfs(adj[v][i])) return 0;
            ret[v] = min(ret[v], ret[adj[v][i]]);
        } else {
            if (cmp[adj[v][i]] != -1) continue;
            ret[v] = min(ret[v], pre[adj[v][i]]);
        }
    }

    if (pre[v] <= ret[v]) return isStrong(v);
    return 1;
}

int main () {
    int t;
    scanf("%d", &t);

    while (t--) {
        adj[N*N*4].clear();
        pre[N*N*4] = cmp[N*N*4] = -1;
        cmpcnt = blccnt = whtcnt =  cnt = 0;
        while (!st.empty()) st.pop();

        scanf("%d %d", &n, &m);
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf(" %c", &at);
                
                mat[i*m+j] = -1;
                if (at == 'W') {
                    whtcnt++;
                    mat[i*m+j] = -2;
                } else if (at == 'B') {
                    for (int k = 0; k < 4; k++) {
                        adj[blccnt*4+k].clear();
                        adj[N*N*4].push_back(blccnt*4+k);
                        pre[blccnt*4+k] = cmp[blccnt*4+k] = -1;
                    }

                    mat[i*m+j] = blccnt++;
                }
            }
        }

        if (whtcnt != 2*blccnt) {
            printf("NO\n");
            continue;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (isBlk(i, j) <= 0) continue;
                src = mat[i*m+j]*4;
                //printf("> %d\n", src/4);

                for (int k = 0; k < 4; k++) {
                    if (isBlk(i+dl[k], j+dc[k]) < 0) continue;
                    //printf("==> %d\n", k);
                    adj[src+k].push_back(src+(k+2)%4);
                }

                for (int k = 4; k < 12; k++) {
                    if (isBlk(i+dl[k], j+dc[k]) <= 0) continue;
                    dst = mat[(i+dl[k])*m + j+dc[k]]*4;
                    //printf("==> %d (%d)\n", k, dst);
                    
                    if (k < 8)
                        adj[src+k%4].push_back(dst+k%4);
                    else {
                        adj[src+k%4].push_back(dst+(k+1)%4);
                        adj[src+(k+1)%4].push_back(dst+k%4);
                    }
                }
            }
        }

/*
        for (int i = 0; i < blccnt*4; i++) {
            printf("%d %d(%d) -> ", i, i/4, i%4);
            for (int j = 0; j < adj[i].size(); j++)
                printf("%d %d(%d) ", adj[i][j], adj[i][j]/4, adj[i][j]%4);
            printf("\n");
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                printf("%d ", mat[i*m+j]);
            printf("\n");
        }
*/

        if (dfs(N*N*4)) printf("YES\n");
        else printf("NO\n");
    }
}
