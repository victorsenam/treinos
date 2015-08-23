#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef ll num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 100007
#define w first
#define d second

int n, m, s, t;
int a, b, aux;
num l;
vector<pair<num, int> > adj[N][2];
num dist[N][2];
priority_queue<pair<num, int> > pq;
pair<num, int> v;

void djs (int src, bool ty) {
    pq.clear();

    pq.push_back(make_pair(0ll, src));
    dist[src] = 0;

    for (int i = 0; i < n; i++)
        dist[i][ty] = LLONG_MAX;

    while (!pq.empty()) {
        v = pq.top();
        pq.pop();

        if (dist[v.d] < v.w)
            continue;

        for (int i = 0; i < adj[v.d][ty].size(); i++) {
            if (dist[adj[v.d][ty][i].d] <= v.w + adj[v.d][ty][i].d) continue;
            dist[adj[v.d][ty][i].d] = v.w + adj[v.d][ty][i].d;
            pq.push(adj[v.d][ty][i].d);
        }
    }
}

int main () {
    scanf("%d %d %d %d", &n, &m, &s, &t);

    s--;
    t--;

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &a, &b, &aux);
        a--; b--;
        l = aux;
        adj[a][0].push_back(make_pair(l, b));
        adj[b][1].push_back(make_pair(l, a));
    }

    djs(s, 0);
    djs(t, 1);

    for (int i = 0; i < n; i++) {
        
    }
}
