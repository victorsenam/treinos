#include <bits/stdc++.h>

using namespace std;

#define N 501
#define M 101

bool v[N];
int vs, n, m;
pair<int, int> cid[N];
vector<int> conf[M];

bool dfs(int i, int co) {
    int c;
    v[i] = 1;
    vs++;
    if (vs == n) return 1;

    if (cid[i].first == co) c = cid[i].second;
    else c = cid[i].first;
    
    /*
    printf("%d -> %d -> %d (", co, i, c);
    for (int j = 0; j < n; j++) printf("%d ", v[j]);
    printf(")\n");
    */

    for (int j = 0; j < conf[c].size(); j++) {
        if (v[conf[c][j]]) continue;
        if (dfs(conf[c][j], c)) return 1;
    }
    v[i] = 0;
    vs--;
    return 0;
}

int main () {
    int a, x, i;

    while (scanf("%d %d", &n, &m) != EOF && n && m) {
        for (i = 0; i < n; i++) {
            v[i] = 0;
            cid[i].first = cid[i].second = -1;
        }
        for (i = 0; i < m; i++) {
            conf[i].clear();
            scanf("%d", &a);
            for (int j = 0; j < a; j++) {
                scanf("%d", &x);
                conf[i].push_back(x);
                if (cid[x].first == -1) cid[x].first = i;
                else cid[x].second = i;
            }
        }
        for (i = 0; i < n; i++) {
            if (cid[i].first == -1) break;
            if (cid[i].second == -1) cid[i].second = cid[i].first;
        }
        if (i < n) {
            printf("-1\n");
            continue;
        }

        for (i = 0; i < n; i++) {
            vs = 0;
            if (dfs(i, cid[i].first)) break;
            if (cid[i].first == cid[i].second) continue;
            vs = 0;
            if (dfs(i, cid[i].second)) break;
        }

        if (i >= n) printf("-1\n");
        else printf("%d\n", i);
    }
}
