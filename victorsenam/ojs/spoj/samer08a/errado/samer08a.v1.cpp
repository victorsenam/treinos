#include <bits/stdc++.h>

using namespace std;

#define MAX 500

class vert {
public: 
    int w, n;
    bool operator< (const vert c) const {
        return w < c.w;
    }
};

struct edge {
    int from, to, w;
};

priority_queue<vert> fila;
queue<edge> regr;
int v, e, f, t;
int a, b, w;
vert verts[MAX];
vector<edge> adj[MAX];
edge ed;
vert nd;

int main ( ) {
    while(scanf("%d %d", &v, &e) != EOF && v && e) {
        scanf("%d %d", &f, &t);
        for (int i = 0; i < e; i++) {
            scanf("%d %d %d", &a, &b, &w);
            ed.to = b;
            ed.from = a;
            ed.w = w;
            adj[a].push_back(ed);
            ed.to = a;
            ed.from = b;
            adj[b].push_back(ed);
        }
        for (int i = 0; i < v; i++) {
            verts[i].w = -1;
            verts[i].n = i;
        }
        verts[f].w = 0;
        fila.push(verts[f]);

        while (!fila.empty()) {
            nd = fila.top();
            fila.pop();

            for (int i = 0; i < adj[nd.n].size(); i++) {
                if (verts[adj[nd.n][i].to].w == -1 || verts[adj[nd.n][i].to].w > nd.w + adj[nd.n][i].w) {
                    verts[adj[nd.n][i].to].w = nd.w + adj[nd.n][i].w;
                    fila.push(verts[adj[nd.n][i].to]);
                }
            }
        }

        for (int i = 0; i < adj[t].size(); i++) {
            regr.push(adj[t][i]);
        }

        while (!regr.empty()) {
            ed = regr.front();
            regr.pop();
            
            if (ed.w != -1 && verts[ed.to].w + ed.w == verts[ed.from].w) {
                for (int i = 0; i < adj[ed.to].size(); i++) {
                    if (adj[ed.to][i].to = ed.from && adj[ed.to][i].w == ed.w) adj[ed.to][i].w = -1;
                    else regr.push(adj[ed.to][i]);
                }
                for (int i = 0; i < adj[ed.from].size(); i++) if (adj[ed.from][i].to = ed.to && adj[ed.from][i].w == ed.w) adj[ed.from][i].w = -1;
            }
        }
        for (int i = 0; i < v; i++) {
            printf("%d(%d) -> ", i, verts[i].w);
            for (int j = 0; j < adj[i].size(); j++) printf("%d(%d) ", adj[i][j].to, adj[i][j].w);
            printf("\n");
        }

        for(int i = 0; i < v; i++) verts[i].w = -1;

        fila.push(verts[f]);
        while (!fila.empty() ) {
            nd = fila.top();
            fila.pop();

            for (int i = 0; i < adj[nd.n].size(); i++) {
                if (adj[nd.n][i].w != -1 && (verts[adj[nd.n][i].to].w == -1 || verts[adj[nd.n][i].to].w > nd.w + adj[nd.n][i].w)) {
                    verts[adj[nd.n][i].to].w = nd.w + adj[nd.n][i].w;
                    if (adj[nd.n][i].to == t) goto endloop;
                    fila.push(verts[adj[nd.n][i].to]);
                }
            }
        }
endloop:
        printf("%d\n", verts[t].w);
        for (int i = 0; i < e; i++) adj[i].clear();

        while (!fila.empty()) fila.pop();
    }  
}
