#include <bits/stdc++.h>

using namespace std;

const int N = 102;

struct vert {
    int v, o, w, f, p, ff;

    bool operator < (const vert & a) const {
        return w > a.w;
    }
};

struct edge {
    int v, w, id;
};

int turn;
int n, m;
int a, b, l;
int from[N][N][N];
int visi[N][N][N];
int turn;
int sol[N];
int ss;
vector<edge> adj[N];
priority_queue<vert> pq;

int main () {
    while (scanf("%d %d", &n, &m) != EOF && n != -1) {
        for (int i = 0; i < n; i++)
            adj[i].clear();
        turn++;

        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &a, &b, &l);
            a--; b--;
            edge aux;
            aux.id = i;
            aux.w = l;
            aux.v = b;
            adj[a].push_back(aux);
            aux.v = a;
            adj[b].push_back(aux);
        }

        while (!pq.empty())
            pq.pop();

        for (int i = 0; i < n; i++) {
            vert fs;
            fs.v = fs.o = fs.f = fs.ff = i;
            fs.w = 0;
            fs.p = -1;
            pq.push(fs);
        }

        vert res;
        res.v = res.o = res.f = res.ff = res.p = -1;
        res.w = INT_MAX;
        while (!pq.empty()) {
            vert att = pq.top();
            pq.pop();

            if (att.w > res.w)
                continue;

            if (visi[att.o][att.f][att.v] == turn)
                continue;
            from[att.o][att.f][att.v] = att.ff;
            visi[att.o][att.f][att.v] = turn;

            for (int i = 0; i < adj[att.v].size(); i++) {
                if (adj[att.v][i].v == att.f)
                    continue;

                vert aux = att;
                aux.w += adj[att.v][i].w;
                aux.ff = att.f;
                aux.f = att.v;
                aux.v = adj[att.v][i].v;
                aux.p = adj[att.v][i].id;
                
                if (aux.v == aux.o && aux.w < res.w)
                    res = aux;
                else
                    pq.push(aux);
            }
        }

        if (res.v == -1) {
            printf("No solution.\n");
            continue;
        }

        printf("%d", res.v+1);
        res.v = res.f;
        res.f = res.ff;
        while (res.v != res.o) {
            printf(" %d", res.v+1);

            res.ff = from[res.o][res.f][res.v];
            res.v = res.f;
            res.f = res.ff;
        }
        printf("\n");
    }
}
