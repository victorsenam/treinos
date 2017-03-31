#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 7e3+7;

int ty[N];
vector<int> adj[N];
int n;
queue<pii> qu;

int go (int t) {
    for (int i = 0; i < n; i++)
        ty[i] = -1;
    while (!qu.empty())
        qu.pop();
    qu.push(pii(t,0));

    printf("GO %d\n", t);
    while (!qu.empty()) {
        int b = qu.front().first;
        int u = qu.front().second;
        qu.pop();

        printf("%d %d\n", b, u);

        if (ty[u] != -1) continue;
        ty[u] = b;

        for (int v : adj[b]) {
            pii nxt(!b, (u - v + n)%n);

            if (ty[nxt.first] != -1) continue;
            qu.push(nxt);
        }
    }

    for (int i = 1; i < n; i++) {
        if (ty[i] == t)
            printf("Win ");
        else if (ty[i] == !t)
            printf("Lose ");
        else
            printf("Loop ");
    }
    printf("\n");
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < 2; i++) {
        int k;
        scanf("%d", &k);

        for (int j = 0; j < k; j++) {
            int a;
            scanf("%d",&a);
            adj[i].push_back(a);
        }
    }
    
    go(0);
    go(1);
}
