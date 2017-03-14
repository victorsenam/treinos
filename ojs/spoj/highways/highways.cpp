#include <bits/stdc++.h>

using namespace std;

#define MAX 100000

class vert {
public:
    int d, n;
    bool operator < (const vert &e) const {
        return d > e.d;
    }
};

class edge {
public:
    int to, w;
};

vector<vert> verts;
vector<edge> edges[MAX];
vert ve;
edge ed;
int t, v, e, s, o;
int a, b, w;

priority_queue<vert> fila;

int main() {
    scanf("%d", &t);

    while (t--) {
        verts.clear();
        while(!fila.empty()) fila.pop();

        scanf("%d %d %d %d", &v, &e, &s, &o);
        
        ve.d = -1;
        for (int i = 0; i < v; i++) {
            ve.n = i;
            verts.push_back(ve);
            edges[i].clear();
        }

        verts[s-1].d = 0;
        fila.push(verts[s-1]);

        for (int i = 0; i < e; i++) {
            scanf("%d %d %d", &a, &b, &w);
            ed.to = b-1;
            ed.w = w;
            edges[a-1].push_back(ed);
            ed.to = a-1;
            edges[b-1].push_back(ed);
        }

        while(!fila.empty()) {
            ve = fila.top();
            fila.pop();

            if (ve.n == o-1) break;
            for (int i = 0; i < edges[ve.n].size(); i++) {
                if (verts[edges[ve.n][i].to].d == -1 || verts[edges[ve.n][i].to].d > ve.d + edges[ve.n][i].w) {
                    verts[edges[ve.n][i].to].d = ve.d + edges[ve.n][i].w;
                    fila.push(verts[edges[ve.n][i].to]);
                }
            }
        }
        if (verts[o-1].d == -1) printf("NONE\n");
        else printf("%d\n", verts[o-1].d);
    }
}










