#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e3+8;
const int T = 9000;
const int INF = T+7;

int t;
int n, s;
int b[N];
int d[T];

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &s);

        for (int i = 0; i < n; i++)
            scanf("%d", &b[i]);
        for (int i = 0; i < T; i++)
            d[i] = INF;
        d[0] = 0;

        queue<int> qu;
        qu.push(0);

        while (!qu.empty()) {
            int u = qu.front();
            qu.pop();

            for (int i = 0; i < n; i++) {
                int v = (u + b[i]);
                v = max(v, 0);
                v = min(v, 3600);

                if (d[v] != INF) continue;
                d[v] = d[u] + 1;
                qu.push(v);
            }
        }

        for (int i = s; i <= 3600; i++) {
            if (d[i] != INF) {
                printf("%d %d\n", d[i], i-s);
                break;
            }
        }
    }
}
