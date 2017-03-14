#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define GNU __gnu_pbds

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
namespace GNU { typedef tree<pair<int, int>, null_type, less<pair<int, int> >, rb_tree_tag, tree_order_statistics_node_update> ordered_set; } 
using GNU::ordered_set;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 2e4+7;
const int M = 1e6;

int qr[M][3];
int rp[N];
ordered_set s[N];
int n, m, qs, qt;
int v[N];
double res;
int ed[M][2], st[M];
char c;
int tc;

int find (int u) {
    if (u == rp[u]) return u;
    return rp[u] = find(rp[u]);
}

void join (int u, int v) {
    if ((u = find(u)) == (v = find(v))) return;
    if (s[u].size() > s[v].size()) swap(u, v);
    rp[u] = v;

    for (pair<int, int> it : s[u]) {
        s[v].insert(it);
    }
}

int main () {
    tc = 0;
    while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
        for (int i = 0; i < n; i++) {
            scanf("%d", v+i);
        }

        res = 0;

        for (int i = 0; i < m; i++) {
            scanf("%d %d", &ed[i][0], &ed[i][1]);
            ed[i][0]--;
            ed[i][1]--;
            st[i] = 1;
        }
        
        qt = qs = 0;

        while (scanf(" %c", &c) != EOF && c != 'E') {
            if (c == 'D') {
                qr[qs][0] = 0;
                scanf("%d", &qr[qs][1]);
                st[--qr[qs][1]] = 0;
                qs++;
            } else if (c == 'Q') {
                qr[qs][0] = 1;
                scanf("%d %d", &qr[qs][1], &qr[qs][2]);
                qr[qs++][1]--;
            } else if (c == 'C') {
                qr[qs][0] = 2;
                scanf("%d %d", &qr[qs][1], &qr[qs][2]);
                qr[qs][1]--;
                swap(v[qr[qs][1]], qr[qs][2]);
                qs++;
            }
        }

        for (int i = 0; i < n; i++) {
            s[i].clear();
            s[i].insert({v[i], i});
            rp[i] = i;
        }

        for (int i = 0; i < m; i++)
            if (st[i])
                join(ed[i][0], ed[i][1]);
        
        for (int i = qs-1; i >= 0; i--) {
            int ty = qr[i][0];
            if (ty == 0) {
                int a = qr[i][1];
                join(ed[a][0], ed[a][1]);
            } else if (ty == 1) {
                int u = find(qr[i][1]);
                int x = qr[i][2];
                qt++;

                int aux;
                if (x <= 0 || x > s[u].size()) aux = 0;
                else aux = pair<int, int>(*s[u].find_by_order(s[u].size() - x)).first;
                res += aux;
            } else {
                int u = qr[i][1];
                int r = find(u);
                int x = qr[i][2];
                s[r].erase({v[u], u});
                v[u] = x;
                s[r].insert({v[u], u});
            }
        }

        res /= qt;
        printf("Case %d: %.6f\n", ++tc, res);
    }
}
