#include <bits/stdc++.h>
#include <ext/pb_ds/detail/standard_policies.hpp>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define lld I64d
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 400007;

template<typename Key, // Key type
 typename Mapped, // Mapped-policy
 typename Cmp_Fn = less<Key>, // Key comparison functor
 typename Tag = rb_tree_tag, // Specifies which underlying data structure to use
 template<
 typename Const_Node_Iterator,
 typename Node_Iterator,
 typename Cmp_Fn_,
 typename Allocator_>
 class Node_Update = null_node_update, // A policy for updating node invariants
 typename Allocator = std::allocator<char> > // An allocator type
 class tree;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ordered_set mp[N];
int curr[N], cs;
int hd[N], to[N], nx[N], val[N], es;
int deg[N];
int a[N];
int qu[N], qi, qf;
int pai[N];

void insert (int u, int x) {
    if (curr[u] == 0)
        curr[u] = cs++;

    mp[curr[u]].insert(x);
}

void join (int u, int v) {
    if (curr[u] == 0)
        curr[u] = cs++;
    if (curr[v] == 0)
        curr[v] = cs++;
    u = curr[u]; v = curr[v];

    if (mp[u].size() > mp[v].size()) swap(u, v);
    
    while (mp[u].size()) {
        int x = *(mp[u].begin());
        mp[v].insert(x);
        mp[u].erase(mp[u].begin());
    }
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", a+i);
    }

    to[0] = -1;
    es = 2;
    cs = 1;
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        nx[es] = hd[a]; to[es] = b; hd[a] = es++;
        nx[es] = hd[b]; to[es] = a; hd[b] = es++;
        deg[a]++;
        deb[b]++;
    }

    for (int i = 0; i < n; i++) {
        if (deg[i] == 1)
            qu[qf++] = i;
    }

    while (qi < qf) {
        int u = qu[qi++];
        deg[u]--;

        insert(u, a[u]);

        for (pai[u] = hd[u]; pai[u] && deg[pai[u]] == 0; pai[u] = nx[pai[u]]);

        val[pai[u]^1] = curr[u].order_of_key(a[pai[u]]);

        join(pai[u], u);

        val[pai[u]] = a[i]-1;

        for (int ed = hd[u]; ed; ed = nx[ed]) {
            if (ed == pai[u]) continue;
            val[pai[u]] -= val[ed];
        }
    }
}
