#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e7+7;

int n;
ll v[N];
int ch[N][2], lm[N][2], vl[N][2], es;
vector<int> adj[N];

void create (int & u, int l, int r) {
    if (u) return;
    u = es++;
    lm[u][0] = l;
    lm[u][1] = r;
    vl[u][0] = vl[u][1] = -1;
    ch[u][0] = ch[u][1] = 0;
}

inline ll optm (ll a, ll b, bool ty) {
    if (a == -1) return b;
    if (b == -1) return a;
    if (ty) return max(a,b);
    return min(a,b);
}

void set (int & u, int l, int r, int p, ll x) {
    create(u,l,r);
    if (l == r) {
        for (int k = 0; k < 2; k++)
            vl[u][k] = optm(vl[u][k], x, k);
    } else {
        int mid = (l+r)/2;
        set(ch[u][0], l, mid, p, x);
        set(ch[u][1], mid+1, r, p, x);

        for (int k = 0; k < 2; k++)
            vl[u][k] = optm(vl[ch[u][0]][k], vl[ch[u][1]][k], k);
    }
}

ll get (int & u, int l, int r, bool ty) {
    create(u,l,r);
    if (!u || lm[u][0] > r || lm[u][1] < l)
        return -1;
    if (lm[u][0] <= l && r <= lm[u][1])
        return vl[u][ty];
    
    return optm(get(ch[u][0], l, r, ty), get(ch[u][1], l, r, ty), ty);
}

int main () {
    es = 1;

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);

    for (int i = 1; i < n; i++) {
        int a;
        scanf("%d", &a);

        adj[a-1].push_back(i);
    }
}
