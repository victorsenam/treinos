#include <bits/stdc++.h>

using namespace std;

#define N 100

bool reach[N];
vector<pair<int, int> > adj[N];
int a, b, w, n, m;
priority_queue<pair<int, pair<int, int> > > pq;
pair<int, int> att;

void insert(int v) {
    if (reach[v]) return;
    reach[v] = 1;

    for (int i = 0; i < adj[v].size(); i++) {
        if (reach[adj[v][i].first]) continue;
        pq.push(make_pair(-adj[v][i].second, make_pair(v, adj[v][i].first)));
    }
}

int main () {
    int t = 0;
    while (scanf("%d %d", &n, &m) != EOF && n && m) {
        for (int i = 0; i < n; i++) {
            reach[i] = 0;
            adj[i].clear();
        }
        while (!pq.empty()) pq.pop();

        for (int i = 0; i < m ; i++) {
            scanf("%d %d %d", &a, &b, &w);
            adj[a-1].push_back(make_pair(b-1, w));
            adj[b-1].push_back(make_pair(a-1, w));
        }

        insert(0);

        printf("Teste %d\n", ++t);
        while (!pq.empty()) {
            att = pq.top().second;
            pq.pop();
            
            if (reach[att.first] && reach[att.second]) continue;

            printf("%d %d\n", min(att.first, att.second)+1, max(att.first, att.second)+1);
            if (reach[att.first]) insert(att.second);
            else insert(att.first);
        }
        printf("\n");
    }
}
