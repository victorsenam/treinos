#include <bits/stdc++.h>

using namespace std;

#define MAX 1000

int t, n, m, h[MAX];
int memo[MAX][MAX];

int pd(int from, int to) {
    int r, s;
    if (to == n) return 0;
    if (from != -1 && memo[from][to] != -1) return memo[from][to];
    r = pd(from, to+1);
    s = 0;
    if (from == m || from == -1 || h[from] > h[to]) s = pd(to, to+1) + 1;
    if (s > r) r = s;
    if (from != -1) memo[from][to] = r;
    return r;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++) {
            scanf("%d", &(h[i]));
            for (int j = 0; j < n; j++) memo[i][j] = -1;
        }
        
        printf("%d\n", pd(-1, 0));
    }
}
