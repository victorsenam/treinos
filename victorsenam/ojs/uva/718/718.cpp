#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef ll num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 102

int e, t;
num ini, fim, r, s, maxi, f;
pair<num, num> x, y;
bool v[N];
vector<int> adj[N];
pair<num, num> ele[N];

bool dfs(int u) {
    if (u == e+1) return 1;
    if (v[u]) return 0;

    v[u] = 1;

    for (int i = 0; i < adj[u].size(); i++)
        if(dfs(adj[u][i]))
            return 1;
    
    return 0;
}

num divfloor(num a, num b) {
    if (a < 0 && b < 0) return -divfloor(-a, -b);
    if (b < 0) return divfloor(-a, -b);

    if (a > 0 || a%b == 0) return a/b;
    return a/b-1;
}

num euclid (num a, num * k, num b, num * l) {
    if (a < 0) {
        *k = -*k;
        return euclid(-a, k, b, l);
    }
    if (b < 0) {
        *l = -*l;
        return euclid(a, k, -b, l);
    }
    if (a%b == 0) {
        *k = 0;
        *l = 1;
        return b;
    }
    num d = euclid(b, k, a%b, l);
    num aux = *k;
    *k = *l;
    *l = aux - *l*(a/b);
    return d;
}

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d %d", &f, &e, &ini, &fim);
        for (int i = 0; i < e+2; i++) {
            adj[i].clear();
            v[i] = 0;
        }

        for (int i = 0; i < e; i++)
            scanf("%d %d", &ele[i].first, &ele[i].second);

        for (int i = 0; i < e; i++) {
            x = ele[i];
            if ((ini - x.second)%x.first == 0) {
                adj[i].push_back(e);
                adj[e].push_back(i);
            }
            if ((fim - x.second)%x.first == 0) {
                adj[i].push_back(e+1);
                adj[e+1].push_back(i);
            }
            for (int j = i + 1; j < e; j++) {
                num m, k, l, d;
                y = ele[j];
                d = y.second - x.second;
                m = euclid(x.first, &k, -y.first, &l);

                if (d%m) continue;
                
                k %= y.first/m;
                k *= d/m;
                
                r = abs(x.first*y.first/m);
                s = ((x.first*k + x.second)%r+r)%r;
                // r and s always positive

                maxi = r*divfloor(f-1-s, r)+s;

                // printf("(%d,%d) -> (%d)*h + (%d) -> %d\n", i, j, r, s, maxi);
                if (maxi >= max(x.second, y.second)) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

    /*
        for (int i = 0; i < e; i++) {
            for (int j = 0; j < adj[i].size(); j++) {
                printf("%d <-> %d\n", i, adj[i][j]);
            }
        }
    */

        if (dfs(e))
            printf("It is possible to move the furniture.\n");
        else
            printf("The furniture cannot be moved.\n");
    }
}
