#include <bits/stdc++.h>

using namespace std;

const int N = 10007;

int n, m, a, b, t;
vector<int> adj[N];
deque<int> q;
int deg[N];
int sol[N];
int ss;

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            deg[i] = 0;
        }

        for (int i = 0; i < m; i++) {
            scanf("%d %d", &a, &b);
            a--;
            b--;
            adj[a].push_back(b);
            deg[b]++;
        }

        for (int i = 0; i < n; i++) 
            if(deg[i] == 0) 
                q.push_back(i);
        int sn = 0;

        do {
            if (q.size() > 1) {
                printf("missing hints\n");
                break;
            } else if (q.size() == 0) {
                printf("recheck hints\n");
                break;
            } else {
                int las = q.front();
                q.pop_front();

                sol[sn++] = las;
                for (int i = 0; i < adj[las].size(); i++) {
                    deg[adj[las][i]]--;
                    if (deg[adj[las][i]] == 0) {
                        q.push_back(adj[las][i]);
                        ss++;
                    } 
                }
            }
        } while(sn < n);
        q.clear();

        if (sn == n) {
            for (int i = 0; i < n; i++) {
                printf("%d ", sol[i]+1);
            }
            printf("\n");
        }
    }
}
