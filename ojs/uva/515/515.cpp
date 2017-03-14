#include <bits/stdc++.h>

using namespace std;

const int N = 107;

typedef long long int num;

vector<pair<int, num> > adj[N+3];
num dist[N];
int n, m, a, b;
num d;
char c, aux;

int main () {
    while (scanf("%d %d", &n, &m) != EOF && (n && m)) {
        for (int i = 0; i <= n+1; i++) {
            adj[i].clear();
            dist[i] = 0;
        }

        for (int i = 0; i < m; i++) {
            scanf("%d %d %c%c %lld", &a, &b, &c, &aux, &d);
            b += a;
            a--;
            if (c == 'l')
                adj[a].push_back(make_pair(b, d-1));
            else
                adj[b].push_back(make_pair(a, -d-1));
        }

/*
        for (int i =0 ; i <= n; i++) {
            printf("%d: ", i);
            for (int j =0 ; j < adj[i].size(); j++)
                printf("%d(%lld) ", adj[i][j].first, adj[i][j].second);
            printf("\n");
        }
*/

        bool chn;
        for (int k = 0; k <= n+1; k++) {
            chn = 0;
            for (int i = 0; i <= n; i++) {
                for (int j = 0; j < adj[i].size(); j++) {
                    if (dist[adj[i][j].first] <= adj[i][j].second + dist[i]) continue;
                    chn = 1;
                    dist[adj[i][j].first] = adj[i][j].second + dist[i];
                }
            }
            if (!chn) break;
        }

        if (chn)
            printf("successful conspiracy\n");
        else
            printf("lamentable kingdom\n");
    }
}
