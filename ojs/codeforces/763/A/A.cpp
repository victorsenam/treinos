#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+7;

int n;
int deg[N];
vector<int> adj[N];
int c[N];
int rs[N];

bool go (int u, int cr, int pr) {
    if (cr != c[u]) return 0;

    for (int x : adj[u])
        if (x != pr && !go(x, cr, u))
            return 0;

    return 1;
}

void testit (int u) {
    for (int x : adj[u])
        if (!go(x, c[x], u)) {
            printf("NO\n");
            exit(0);
        }
    
    printf("YES\n%d\n", u+1);
    exit(0);
}

int main () {
    scanf("%d", &n);

    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a-1].pb(b-1);
        adj[b-1].pb(a-1);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &c[i]);
        deg[i] = adj[i].size();
    }

    deque<int> qu;
    for (int i = 0; i < n; i++)
        if (adj[i].size() == 1)
            qu.pb(i);

    while (!qu.empty()) {
        int u = qu.front();
        qu.pop_front();

        for (int x : adj[u]) {
            if (!rs[x]) {
                deg[x]--;
                if (deg[x] == 1)
                    qu.pb(x);
            } else {
                if (c[u] != rs[x])
                    testit(u);
            }
        }

        rs[u] = c[u];
    }

    printf("YES\n1\n");
}
