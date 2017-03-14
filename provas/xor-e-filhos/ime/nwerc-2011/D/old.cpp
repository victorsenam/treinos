#include <bits/stdc++.h>

using namespace std;

const int N = 503; 

const int mi[4] = {1, -1, 0, 0};
const int mj[4] = {0, 0, 1, -1};

vector<int> adj[8*N*N];
vector<int> inv[8*N*N];
char mat[N][N];
int idx[N][N];
int n, m;
int q, ctw, ctb;
int t;
int turn;
int visi[8*N*N];
int labe[8*N*N];
stack<int> st;

bool isval (int i, int j) {
    if (i < 0 || i >= n)
        return 0;
    if (j < 0 || j >= m)
        return 0;
    return 1;
}

void pdfs (int u) {
    if (visi[u] == turn)
        return;
    visi[u] = turn;    

    for (int i = 0; i < adj[u].size(); i++) {
        pdfs(adj[u][i]);
    }

    st.push(u);
}

void dfs (int u, int lb) {
    if (labe[u] != -1)
        return;
    labe[u] = lb;

    for (int i = 0; i < inv[u].size(); i++)
        dfs(inv[u][i], lb);
}

int main () {
    scanf("%d", &t);

    while (t--) {
        q = 0;
        ctw = ctb = 0;
        while (!st.empty()) 
            st.pop();
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; i++) {
            scanf(" %s", mat[i]);
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == '.')
                    idx[i][j] = -1;
                else {
                    idx[i][j] = q++;
                    if (mat[i][j] == 'W')
                        ctw++;
                    else
                        ctb++;
                }
            }
        }

        if (ctw != 2*ctb) {
            printf("NO\n");
            continue;
        }

        for (int  i= 0; i < 8*q; i++) {
            adj[i].clear();
            inv[i].clear();
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == -1)
                    continue;
                int id = idx[i][j];

                if (mat[i][j] == 'B') {
                    adj[4*id+0].push_back(4*id+4*q+1);
                    adj[4*id+1].push_back(4*id+4*q+0);
                    adj[4*id+2].push_back(4*id+4*q+3);
                    adj[4*id+3].push_back(4*id+4*q+2);
                    adj[4*id+4*q+0].push_back(4*id+1);
                    adj[4*id+4*q+1].push_back(4*id+0);
                    adj[4*id+4*q+2].push_back(4*id+3);
                    adj[4*id+4*q+3].push_back(4*id+2);

                    for (int k = 0; k < 4; k++) {
                        if (!isval(i+mi[k], j+mj[k]) || mat[i+mi[k]][j+mj[k]] != 'W')
                            adj[4*id+k].push_back(4*id+4*q+k);
                        else
                            adj[4*id+k].push_back(4*idx[i+mi[k]][j+mj[k]]+(k^1));
                    }
                } else {
                    for (int k = 0; k < 4; k++) {
                        for (int l = 0; l < 4; l++) {
                            if (k == l)
                                continue;
                            adj[4*id+k].push_back(4*id+4*q+l);
                        }

                        if (!isval(i+mi[k], j+mj[k]) || mat[i+mi[k]][j+mj[k]] != 'B')
                            adj[4*id+k].push_back(4*id+4*q+k);
                        else
                            adj[4*id+k].push_back(4*idx[i+mi[k]][j+mj[k]]+(k^1));
                    }
                }
            }
        }

        printf("== %d w%d b%d\n", q, ctw, ctb);
        /*
        for (int i = 0; i < 8*q; i++) {
            printf("%d dir %d status %d\n", (i/4)%q, i%4, (i < 4*q));
            for (int j = 0; j < adj[i].size(); j++) {
                int a = adj[i][j];
                printf("\t%d dir %d status %d\n", (a/4)%q, a%4, (a < 4*q));
            }
        }
        */

        bool ok = 1;
        for (int i = 0; i < 8*q; i++)
            for (int j = 0; j < adj[i].size(); j++)
                inv[adj[i][j]].push_back(i);
        turn++;
        for (int i = 0; i < 8*q; i++)
            pdfs(i);

        memset(labe, -1, sizeof labe);
        int lb = 0;
        while (!st.empty()) {
            if (labe[st.top()] == -1)
                dfs(st.top(), lb++);
            st.pop();
        }

        for (int i = 0; i < 4*q; i++) {
            if (labe[i] == labe[i+4*q])
                ok = 0;
        }

        if (ok)
            printf("YES\n");
        else
            printf("NO\n");
    }
}
