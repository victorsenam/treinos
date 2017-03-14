#include <bits/stdc++.h>

using namespace std;

#define MAX 500

class vertex {
public:
    int n;
    int s;
    inline bool operator< (const vertex comp) const {
        return s > comp.s;
    }
};

class edge {
public:
    int to;
    int from;
    int w;
};

/* Dados */
priority_queue<vertex> fila; // Fila Prioritária, para calcular djikstra
vector<edge> adj[MAX]; // Lista de Adjacências
vertex verts[MAX]; // Vértices e Distâncias

/* Auxiliares */
int a, b, n, w, c, f, e; // Ints auxiliares
vertex vert; // Vértice Temporário
edge edg; // Aresta Temporária

void bfs (int a, int l) {
    for (int i = 0; i < adj[a].size(); i++) {
        if (l == adj[a][i].to && adj[a][i].w + verts[a].s == verts[l].s) {
            adj[a][i].w = -1;
      //      printf("%d <-> %d \n", l, a);
        }
        else if (a == adj[a][i].to && adj[a][i].w + verts[adj[a][i].from].s == verts[a].s) {
            bfs(adj[a][i].from, a);
        }
    }
}

int main () {
    while(scanf("%d %d", &n, &e) && n && e) {
        scanf("%d %d", &c, &f);
        for (int i = 0; i < n; i++) {
            verts[i].n = i;
            verts[i].s = -1;
            adj[i].clear();
        }
        for (int i = 0; i < e; i++) {
            scanf("%d %d %d", &a, &b, &w);
            edg.w = w;
            edg.to = b;
            edg.from = a;
            adj[a].push_back(edg);
            adj[b].push_back(edg);
        }

        verts[c].s = 0;
        fila.push(verts[c]);

        while (!fila.empty()) {
            vert = fila.top();
            fila.pop();

            for (int i = 0; i < adj[vert.n].size(); i++) {
                if (adj[vert.n][i].from == vert.n && (verts[adj[vert.n][i].to].s == -1 || vert.s + adj[vert.n][i].w < verts[adj[vert.n][i].to].s)) {
                    verts[adj[vert.n][i].to].s = vert.s + adj[vert.n][i].w;
                    fila.push(verts[adj[vert.n][i].to]);
                }
            }
        }
    /*
        printf("Pesos dos nós 1:\n");
        for (int i = 0; i < n; i++) {
            printf("%d->%d ", i, verts[i].s);
        }
        printf("\n");
*/
  //      printf("Regressao:\n");
        bfs(f,f);

        for (int i = 0; i < n; i++) {
            verts[i].s = -1;
        }

        verts[c].s = 0;
        fila.push(verts[c]);
        
        while (!fila.empty()) {
            vert = fila.top();
            fila.pop();
            if (vert.n == f) break;
            for (int i = 0; i < adj[vert.n].size(); i++) {
                if (adj[vert.n][i].w == -1) continue;
                if (verts[adj[vert.n][i].to].s == -1 || vert.s + adj[vert.n][i].w < verts[adj[vert.n][i].to].s) {
                    verts[adj[vert.n][i].to].s = vert.s + adj[vert.n][i].w;
                    fila.push(verts[adj[vert.n][i].to]);
                }
            }
        }
 /*       
        printf("Pesos dos nós 2:\n");
        for (int i = 0; i < n; i++) {
            printf("%d->%d ", i, verts[i].s);
        }
        printf("\n");
*/
        printf("%d\n", verts[f].s);

        while (!fila.empty()) fila.pop();
    }
}
