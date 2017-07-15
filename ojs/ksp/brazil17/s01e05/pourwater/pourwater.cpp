#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back
#define fst first
#define snd second

const int N = 55;

int n;
inline bool inside(int i) { return i >= 0 && i < n; }

int di[] = {1, -1, 0, 0, 1, -1, 1, -1};
int dj[] = {0, 0, -1, 1, 1, -1, -1, 1};
vector<pii> all;
int seen[N][N];
char g[N][N];
void go(int i, int j) {
    seen[i][j] = 1;
    if(g[i][j] == '#') return;
    all.pb(pii(i, j));
    for(int d = 0; d < 8; d++)
        if(inside(i + di[d]) && inside(j + dj[d]) && !seen[i + di[d]][j + dj[d]])
            go(i + di[d], j + dj[d]);
}

int main () {
    int i, w;
    scanf("%d", &n);
    for(i = 0; i < n; i++)
        scanf(" %s", g[i]);
    scanf("%d", &w);
    go(0, 1);
    sort(all.begin(), all.end(), greater<pii>());
    for(i = 0; i < w; i++)
        g[all[i].fst][all[i].snd] = '*';
    for(i = 0; i < n; i++)
        puts(g[i]);
}

