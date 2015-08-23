#include <bits/stdc++.h>
#define MAX 10000

using namespace std;

int n, e, a, b, found[MAX];
int val;
vector<int> adj[MAX];

void dfs(int i) {
    if (found[i]) return;
    found[i] = 1;
    for (int j = 0; j < adj[i].size(); j++) {
        dfs(adj[i][j]);
    }
}

int main () {
    scanf("%d %d", &n, &e);
   
    if (n != e+1) {
        printf("NO");
        return 0;
    }

    for (int i = 0; i < e; i++) {
        scanf("%d %d", &a, &b);
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
        found[i] = 0;
    }
    found[n] = 0;

    dfs(0);

    for (int i = 0; i < n; i++) {
        if (!found[i]) {
            printf("NO");
            return 0;
        }
    }

    printf("YES");
}
