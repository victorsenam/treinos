#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
typedef pair<ll, vector<int> > pp;
#define pb push_back

const int N = 407;

int n, ds[2], cs[2];
int dist[N][N];
int visi[N], turn;

ll r_val, p[N];
vector<int> r_vec;

pp get (int k, int u1, int u2, int v, int ty) {
    vector<int> r;
    ll c = 0;
    int cnt = 0;
    
    queue<pii> qu;

    turn++;
    qu.push(pii(u1,0));
    if (u1 != u2)
        qu.push(pii(u2,0));

    while (!qu.empty()) {
        pii att = qu.front();
        if (att.second >= ds[ty]/2)
            break;
        qu.pop();

        if (att.first == k) continue;
        if (visi[att.first] == turn) continue;
        visi[att.first] = turn;
        c += p[att.first];

        for (int ed = hd[att.first]; ed; ed = nx[ed]) {
            pii nxt = att;
            nxt.first = to[ed];
            nxt.second++;

            qu.push(nxt);
        }
    }

    while (!qu.empty()) {
        pii att = qu.front();
        if (att.second > ds[ty]/2) break;
    }
}

int div (int k) {
    
}

int main () {
    scanf("%d", &n);

    for (int k = 0; k < 2; k++)
        scanf("%d %d", &ds[k], &cs[k]);

    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);

    es = 2;
    for (int i = 0; i < n-1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        to[es] = b; nx[es] = hd[a]; hd[a] = es++;
        to[es] = a; nx[es] = hd[b]; hd[b] = es++;
    }
    r_val = LLONG_MAX;

    for (int i = 0; i < n; i++)
        div(i);
}
