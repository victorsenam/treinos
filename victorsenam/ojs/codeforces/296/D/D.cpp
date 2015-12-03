#include <bits/stdc++.h>

using namespace std;
typedef long long int num;

const int N = 507;

num adj[N][N];
int n, q[N];
bool e[N];
num a[N];

int main ( ){
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%I64d", &adj[i][j]);
    for (int i = 0; i < n; i++)
        scanf("%d", q+i);

    for (int k = n-1; k >= 0; k--) {
        q[k]--;
        e[q[k]] = 1;
        
        a[k] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                adj[i][j] = min(adj[i][j], adj[i][q[k]] + adj[q[k]][j]);
                if (e[i] && e[j])
                    a[k] += adj[i][j];
            }
        }
    }

    for (int i = 0; i < n; i++)
        printf("%I64d ", a[i]);
    printf("\n");
}
