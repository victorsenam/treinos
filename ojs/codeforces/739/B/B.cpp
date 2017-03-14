#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define GNU __gnu_pbds

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef pair<ll, int> pii;
namespace GNU { typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set; } 
// null_type pode mudar pra virar map
// multiset e multimap não tem suporte aqui, tem que sair usando pair pelo jeito
// aquele less ali é o comparador, louco né?
using GNU::ordered_set;

#ifdef ONLINE_JUDGE
#define lld I64d
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 2e5+7;
const int M = 2*N;

ordered_set s[N];
ll sh[N];
int a[N], pr[N], c[N];
int deg[N];
int n;
int res[N];
int r[N];
queue<int> qu;

int find (int u) {
    if (r[u] == u) return u;
    return r[u] = find(r[u]);
}

void join (int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return;
    if (s[u].size() < s[v].size()) swap(u, v);

    for (pii x : s[v]) {
        x.first = x.first + sh[v] - sh[u];
        s[u].insert(x);
    }

    s[v].clear();
    r[v] = u;
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        s[i].insert(pii(-a[i], i));
        r[i] = i;
        sh[i] = 0;
    }

    for (int i = 1; i < n; i++) {
        scanf("%d %lld", &pr[i], &c[i]);
        pr[i]--;
        deg[pr[i]]++;
    }

    for (int i = 0; i < n; i++)
        if (deg[i] == 0)
            qu.push(i);

    while (!qu.empty()) {
        int u = qu.front();
        int rp = find(u);
        qu.pop();
        
        res[u] = s[rp].order_of_key(pii(- sh[rp], n+1));
        /*
        printf("%d %d:", u+1, res[u]);
        for (pii x : s[rp])
            printf(" (%lld,%d)", x.first + sh[rp], x.second);
        printf("\n");
        */

        if (!u)
            continue;

        deg[pr[u]]--;
        sh[rp] += c[u];
        join(pr[u], u);
        if (deg[pr[u]] == 0) {
            qu.push(pr[u]);
        }
    }

    for (int i = 0; i < n; i++)
        printf("%d ", res[i]-1);
}
