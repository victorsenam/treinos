#include <bits/stdc++.h>

using namespace std;

const int N = 507;

int v[N];
int adj[N][N];
int n, m, a, b, x;
double maxi;

int main () {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++)
        scanf("%d", v+i);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &a, &b, &x);
        a--; b--;
        adj[a][b] = adj[b][a] = x;
    }
    
    maxi = 0.0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j] == 0)
                continue;

            maxi = max((double)(v[i]+v[j])/(double)adj[i][j], maxi);
        }
    }

    printf("%.15lf\n", maxi);
}
