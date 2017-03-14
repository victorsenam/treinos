#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

const int N = 507;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

int n, m;
int adj[N][N];
int deg[N];
int col[N];

void fail () {
    printf("No\n");
    exit(0);
}

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        
        deg[a]++; deg[b]++;
            adj[a][b] = adj[b][a] = 1;
    }

    for (int i = 0; i < n; i++) {
        deg[i]++;
        adj[i][i] = 1;

        if (deg[i] == n)
            col[i] = 1;
    }

    for (int i = 0; i < n; i++) {
        if (col[i] == 1)
            continue;

        for (int j = 0; j < n; j++) {
            if (col[j] == 1)
                col[j] = 1;
            else if (adj[i][j])
                col[j] = 0;
            else
                col[j] = 2;
        }
        break;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j] && abs(col[i]-col[j]) > 1)
                fail();
            else if (!adj[i][j] && abs(col[i]-col[j]) <= 1)
                fail();
        }
    }
    printf("Yes\n");
    for (int i = 0; i < n; i++)
        printf("%c", 'a'+col[i]);
    printf("\n");
}
