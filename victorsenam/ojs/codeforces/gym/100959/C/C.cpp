#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back
#define fst first
#define snd second

const int N = 212345;
int d[2][N];
int a[N];

int main () {
    int i, j, n;
    scanf("%d", &n);
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);
        //a[i] = (rand() % 10000) + 1;
    sort(a, a + n);

    queue<pii> q;
    int mn = -25001;
    int mx = 25001;
    for(i = mn; i <= mx; i++)
        d[0][i - mn] = d[1][i - mn] = INT_MAX;
    q.push(pii(0, 0)); d[0][0 - mn] = 0;
    while (!q.empty()) {
        pii x = q.front(); q.pop();
        for(i = 0; i < n; i++) {
            int y = (2 * x.fst - 1) * a[i];
            int z = x.snd + y;
            if (z >= mn && z <= mx && d[!x.fst][z - mn] == INT_MAX) {
                d[!x.fst][z - mn] = d[x.fst][x.snd - mn] + 1;
                q.push(pii(!x.fst, z));
            }
        }
    }

    int Q;
    scanf("%d", &Q);
    int s, t;
    while(Q--) {
        scanf("%d %d", &s, &t);
        if((s & 1) != (t & 1)) { puts("-1"); continue; }
        int x = INT_MAX;
        if(d[0][(t - s) / 2 - mn] < INT_MAX) x = min(x, d[0][(t - s) / 2 - mn]);
        for (int i = 0; i < n; i++) {
            int y = 2 * a[i] - s;
            if(d[0][(t - y) / 2 - mn] < INT_MAX) x = min(x, d[0][(t - y) / 2 - mn] + 1);
        }
        if(x == INT_MAX) puts("-1");
        else printf("%d\n", x);
    }
}
