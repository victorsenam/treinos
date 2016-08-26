#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1024+7;

char adj[N][N];
int n;
vector<int> to[N];
int p[N], ps;
int r[N], rs;

bool cmp_t (int i, int j) {
    return to[i].size() > to[j].size();
}

int main () {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++) {
            scanf(" %s", adj[i]);
            to[i].clear();
        }

        ps = 0;
        for (int i = 0; i < n; i++) {
            if (adj[0][i] == '1') {
                p[ps++] = i;
            } else {
                for (int j = 0; j < n; j++) {
                    if (adj[0][j] == '1' && adj[j][i] == '1') {
                        to[j].push_back(i);
                        break;
                    }
                }
            }
        }
        
        sort(p, p+ps);

        rs = 0;

        r[rs++] = 0;
        for (int _i = 0; _i < ps; _i++) {
            int i = p[_i];

            r[rs++] = i;
            for (int j : to[i])
                r[rs++] = j;
            for (int j = to[i].size() + 1; __builtin_popcount(j) != 1; j++)
                r[rs++] = p[--ps];
        }


        for (int j = 1; j < n; j *= 2) {
            for (int i = 0; i < n; i += 2*j) {
                printf("%d %d\n", r[i]+1, r[i+j]+1);
                if (adj[r[i]][r[i+j]] == '0')
                    swap(r[i], r[i+j]);
            }
        }
    }
}
