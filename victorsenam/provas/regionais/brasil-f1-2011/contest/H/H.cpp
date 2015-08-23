#include <bits/stdc++.h>

using namespace std;
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else 
#define debug(...) //
#endif

#define N 100000
#define MAX N*4+1

struct seg {
    int esq[MAX], dir[MAX], lazy[MAX];
    int cnt[3][MAX];
    int temp[3];
    // h e r

    void build (int root, int e, int d) {
        esq[root] = e;
        dir[root] = d;
        lazy[root] = 0;

        cnt[0][root] = 1;
        cnt[1][root] = cnt[2][root] = 0;

        if (d - e == 1) return;
        
        build(2*root, e, e+(d-e)/2);
        build(2*root+1, e+(d-e)/2, d);
        for (int i = 0; i < 3; i++)
            cnt[i][root] = cnt[i][2*root] + cnt[i][2*root+1];
    }

    void update (int root, int e, int d) {
        refresh(root);
        if (e <= esq[root] && d >= dir[root]) {
            lazy[root] = 1;
            refresh(root);
            return;
        }
        if (e >= dir[root] || d <= esq[root])
            return;
        
        update(2*root, e, d);
        update(2*root+1, e, d);
        for (int i = 0; i < 3; i++)
            cnt[i][root] = cnt[i][2*root] + cnt[i][2*root+1];
    }

    void refresh (int root) {
        for (int i = 0; i < 3; i++)
            temp[i] = cnt[i][root];

        for (int i = 0; i < 3; i++)
            cnt[(i+lazy[root])%3][root] = temp[i];

        if (dir[root] - esq[root] > 1) {
            lazy[2*root] += lazy[root];
            lazy[2*root+1] += lazy[root];
        }
        lazy[root] = 0;
    }

    pair<int, int> getHE (int root, int e, int d) {
        refresh(root);
        if (e <= esq[root] && d >= dir[root])
            return make_pair(cnt[0][root], cnt[1][root]);

        if (e >= dir[root] || d <= esq[root])
            return make_pair(0, 0);

        pair<int, int> a = getHE (root*2, e, d);
        pair<int, int> b = getHE (root*2+1, e, d);
        return make_pair(a.first+b.first, a.second+b.second);
    }
};

int n, m;
seg tree;
pair<int, int> res;
int a, b;
char c;

int main () {
    while (scanf("%d %d", &n, &m) != EOF) {
        tree.build(1, 0, n);
        for (int i = 0; i < m; i++) {
            scanf(" %c %d %d", &c, &a, &b);
            if (c == 'C') {
                res = tree.getHE(1, a-1, b);
                printf("%d %d %d\n", res.first, res.second, b - a + 1 - res.first - res.second);
            } else {
                tree.update(1, a-1, b);
            }
        }
        printf("\n");
    }
}
