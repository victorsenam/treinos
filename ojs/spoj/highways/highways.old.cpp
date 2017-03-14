#include <bits/stdc++.h>

using namespace std;

#define MAX 100000

typedef struct {int n; int w;} edge;

vector<int> d(MAX, -1);
int t, v, e, s, o;
int a, b, w;
vector<edge> adj[MAX];
edge at;

class compar {
    public:
        bool operator() (int ea, int eb) const {
            return d[ea] > d[eb];
        }
}

priority_queue<int,vector<int>,compar> fila;

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d %d %d", &v, &e, &s, &o);
        d[s-1] = 0;
        fila.push(s-1);

        for (int i = 0; i < e; i++) {
            scanf("%d %d %d", &a, &b, &w);
            at.n = b-1;
            at.w = w;
            adj[a-1].push_back(at);
            at.n = a-1;
            adj[b-1].push_back(at);
        }

        while (!fila.empty()) {
            a = fila.top();
            fila.pop();

            if (a == o-1) break;
            for (int i = 0; i < adj[a].size(); i++) {
                if (d[adj[a][i].n] == -1 || d[adj[a][i].n] > d[a] + adj[a][i].w) {
                    d[adj[a][i].n] = d[a] + adj[a][i].w;
                    fila.push(adj[a][i].n);
                }
            }
        }
        if (d[o-1] == -1) printf("NONE\n");
        else printf("%d\n", d[o-1]);

        while (!fila.empty()) fila.pop();
        for (int i = 0; i < v; i++) d[i] = -1;
    }
}
