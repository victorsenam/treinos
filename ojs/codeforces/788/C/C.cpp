#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e3+7;
const int M = 50*N;

int dist[2*M];
int n,m;
int can[N];

int main () {
    scanf("%d %d", &n, &m);

    int mn = 1e3+7;
    int mx = 0;

    queue<int> qu;
    for (int i = 0; i < m; i++) {
        int a;
        scanf("%d", &a);
        if (a == n) {
            printf("1\n");
            return 0;
        }
        if (!can[a]) {
            can[a] = 1;
            qu.push(a);   
            dist[a+M] = 1;
        }

        mn = min(mn, a);
        mx = max(mx, a);
        
    }

    if (mn > n || mx < n) {
        printf("-1\n");
        return 0;
    }
    
    while (!qu.empty()) {
        int u = qu.front();
        qu.pop();

        for (int i = 0; i <= 1e3; i++) {
            if (!can[i]) continue;
            int v = u + i - n;

            if (v < -M || v > M || dist[v+M] != 0) continue;
            
            dist[v+M] = dist[u+M] + 1;
            qu.push(v);
        }
    }

    if (dist[M+n] == 0)
        printf("-1\n");
    else
        printf("%d\n", dist[M+n]);
}
