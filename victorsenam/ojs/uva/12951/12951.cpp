#include <bits/stdc++.h>

using namespace std;

const int N = 200007;

int memo[N][2];
int vis[N][2];
int turn;
int k;
int v[N];
int n;

int main () {
    while (scanf("%d %d", &n, &k) != EOF) {
        for (int i = 0; i < n; i++) 
            scanf("%d", v+i);

        memo[n][0] = memo[n][1] = 0;
        
        for (int i = n-1; i >= 0; i--) {
            memo[i][0] = max(memo[i+1][0], memo[i+1][1] - k - v[i]);
            memo[i][1] = max(memo[i+1][1], memo[i+1][0] + v[i]);
        }

        printf("%d\n", memo[0][0]);
    }
}
