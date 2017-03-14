#include <bits/stdc++.h>

using namespace std;

#define first ff
#define second ss

const int N = 103;

struct enemy {
    int linsiz;
    int colsiz;
    int lin, col;
};

vector<int> lin[N];
vector<int> col[N];
vector<enemy> ene;
int mat[N][N], n, m;
enemy aux;
int cnt, last, att;
char c;
vector<int> adj[4*N*N];
int val[4*N*N]; // -1 false, 0 unset, 1 true
int seen[4*N*N];
int seenCmp[4*N*N];
int from[4*N*N];
int pre[4*N*N];
int ret[4*N*N];
int ord;
stack<int> st;
vector<int> comps[4*N*N];
int cmps;

void color(int i, int c) {
    if (val[i])
        return;
    val[i] = c;

    color(i^1, (-1)*c);

    if (c == -1)
        return;

    for (int j = 0; j < adj[i].size(); j++)
        color(adj[i][j], c);
}

void buildCmp(int v) {
    while (st.top() != v) {
        comps[cmps].push_back(st.top());
        from[st.top()] = cmps;
        st.pop();
    }
    comps[cmps].push_back(v);
    from[v] = cmps;
    cmps++;
}

void cmpDfs(int v) {
    if (seenCmp[v]) return;

    seenCmp[v] = 1;

    for (int k = 0; k < comps[v].size(); k++)
        for (int i = 0; i < adj[comps[v][k]].size(); i++)
            cmpDfs(from[adj[comps[v][k]][i]]);           

    if (val[comps[v][0]] == 0)
        color(comps[v][0], 1);
}

int dfs (int i) {
    if (seen[i] == 1)
        return pre[i];
    if (seen[i] == 2)
        return INT_MAX;

    pre[i] = ret[i] = ord++;
    seen[i] = 1;

    for (int j = 0; j < adj[i].size(); j++)
        ret[i] = min(ret[i], dfs(adj[i][j]));

    seen[i] = 2;
    st.push(i);

    if (ret[i] == pre[i])
        buildCmp(i);

    return ret[i];
}

int main () {
    scanf("%d %d", &n, &m);
    
    cnt = 0;

    for (int i = 0; i < n; i++) {
        lin[i].push_back(-1);
        for (int j = 0; j < m; j++) {
            if (!i)
                col[j].push_back(-1);
            scanf(" %c", &c);
            if (c == 'T') {
                lin[i].push_back(cnt);
                col[j].push_back(cnt);
                adj[cnt].clear();
                mat[i][j] = cnt++;
            } else if (c == '#') {
                lin[i].push_back(-1);
                col[j].push_back(-1);
                mat[i][j] = -1;
            } else if (c == 'n') {
                aux.lin = i;
                aux.col = j;
                aux.linsiz = lin[i].size();
                aux.colsiz = col[j].size();
                ene.push_back(aux);
                mat[i][j] = -2;
            } else {
                mat[i][j] = -3;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        last = -1;
        for (int j = 0; j < lin[i].size(); j++) {
            att = lin[i][j];
            if (att != -1 && last != -1) {
                adj[4*last].push_back(4*last+1);
                adj[4*att+1].push_back(4*att);
            }
            last = att;
        }
        lin[i].push_back(-1);
    }

    for (int i = 0; i < m; i++) {
        last = -1;
        for (int j = 0; j < col[i].size(); j++) {
            att = col[i][j];
            if (att != -1 && last != -1) {
                adj[4*last+2].push_back(4*last+3);
                adj[4*att+3].push_back(4*att+2);
            }
            last = att;
        }
        col[i].push_back(-1);
    }

    for (int i = 0; i < ene.size(); i++)  {
        int cim, bai, esq, dir;
        cim = col[ene[i].col][ene[i].colsiz-1];
        bai = col[ene[i].col][ene[i].colsiz];
        esq = lin[ene[i].lin][ene[i].linsiz-1];
        dir = lin[ene[i].lin][ene[i].linsiz];
        
        if ((cim != -1 && bai != -1) || (cim == -1 && bai == -1)) {
            if (esq != -1)
                adj[4*esq+1].push_back(4*esq);
            else
                adj[4*dir].push_back(4*dir+1);
        } else if ((esq != -1 && dir != -1) || (esq == -1 && dir == -1)) {
            if (cim != -1)
                adj[4*cim+3].push_back(4*cim+2);
            else
                adj[4*bai+2].push_back(4*bai+3);
        } else if (cim != -1) {
            if (esq != -1) {
                adj[4*esq+1].push_back(4*cim+2);
                adj[4*cim+3].push_back(4*esq);
            } else {
                adj[4*dir].push_back(4*cim+2);
                adj[4*cim+3].push_back(4*dir+1);
            }
        } else {
            if (esq != -1) {
                adj[4*esq+1].push_back(4*bai+3);
                adj[4*bai+2].push_back(4*esq);
            } else {
                adj[4*dir].push_back(4*bai+3);
                adj[4*bai+2].push_back(4*dir+1);
            }
        }
    }

    ord = 0;
    for (int i = 0; i < 4*cnt; i++)
        dfs(i);

    for (int i = 0; i < cmps; i++)
        cmpDfs(i);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == -1)
                printf("#");
            else if (mat[i][j] == -2)
                printf("n");
            else if (mat[i][j] == -3)
                printf(".");
            else if (val[mat[i][j]*4+1]==1 && val[mat[i][j]*4+2]==1)
                printf("1");
            else if (val[mat[i][j]*4]==1 && val[mat[i][j]*4+2]==1)
                printf("2");
            else if (val[mat[i][j]*4]==1 && val[mat[i][j]*4+3]==1)
                printf("3");
            else if (val[mat[i][j]*4+1]==1 && val[mat[i][j]*4+3]==1)
                printf("4");
            else
                printf("x");
        }
        printf("\n");
    }
}
