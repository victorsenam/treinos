#include <vector>
#include <queue>
#include <cstdio>

using namespace std;

#define N 500

class vertex {
public:
    int n, s;
    friend bool operator< (const vertex& lhs, const vertex& rhs) { 
        return lhs.s > rhs.s; 
    };
};

vector<int> adj[N][N];
vertex verts[N];
priority_queue<vertex> fila;
int v, e, c, f, a, b, w;
vertex act;

int bfs (int t) {
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < adj[i][t].size(); j++) {
            if (verts[i].s + adj[i][t][j] == verts[t].s) {
                adj[i][t][j] = -1;
                bfs(i);
            }
        }
    }
}

int main () {
    while (scanf("%d %d", &v, &e) && v && e) {
        scanf("%d %d", &c, &f);

        for (int i = 0; i < v; i++) {
            verts[i].n = i;
            verts[i].s = -1;
            for (int j = 0; j < v; j++) adj[i][j].clear();
        }

        for (int i = 0; i < e; i++) {
            scanf("%d %d %d", &a, &b, &w);
            adj[a][b].push_back(w);
        }

        verts[c].s = 0;
        fila.push(verts[c]);

        while (!fila.empty()) {
            act = fila.top();
            fila.pop();
            for (int i = 0; i < v; i++) {
                for (int j = 0; j < adj[act.n][i].size(); j++) {
                    if (verts[i].s == -1 || adj[act.n][i][j] + act.s < verts[i].s) {
                        verts[i].s = adj[act.n][i][j] + act.s;
                        fila.push(verts[i]);
                    }
                }
            }
        }
        
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                for (int k = 0; k < adj[i][j].size(); k++) {
                }
            }
        }

        bfs(f);

        for (int i = 0; i < v; i++) verts[i].s = -1;
        verts[c].s = 0;
        fila.push(verts[c]);

        while (!fila.empty()) {
            act = fila.top();
            fila.pop();
            if (act.n == f) break;
            
            for (int i = 0; i < v; i++) {
                for (int j = 0; j < adj[act.n][i].size(); j++) {
                    if (adj[act.n][i][j] == -1) continue;
                    if (verts[i].s == -1 || adj[act.n][i][j] + act.s < verts[i].s) {
                        verts[i].s = adj[act.n][i][j] + act.s;
                        fila.push(verts[i]);
                    }
                }
            }
        }
        
        while (!fila.empty()) {
            fila.pop();
        }

        printf("%d\n", verts[f].s);
    }
}
