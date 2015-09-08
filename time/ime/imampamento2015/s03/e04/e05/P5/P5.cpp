#include <bits/stdc++.h>

using namespace std;

const int N = 9;
const int M = 24;

struct res {
    int a, b, c;
};

int v[N];
res cond[M];
int n, m;
int a, b, c;

bool solve() {
    int de, da;
    for (int i = 0; i < m; i++) {
        de = max(cond[i].c, -cond[i].c);
        da = v[cond[i].a] - v[cond[i].b];
        da = max(da, -da);
        if (cond[i].c > 0) {
            if (da > de)
                return 0;
        } else {
            if (da < de)
                return 0;
        }
    }
    return 1;
}

int main () {
    while (scanf("%d %d", &n, &m) != EOF && n) {
        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &cond[i].a, &cond[i].b, &cond[i].c);
        }

        for (int i = 0; i < n; i++)
            v[i] = i;
        
        int cnt = 0;
        do {
            if (solve()) cnt++;
        } while (next_permutation(v, v+n));

        printf("%d\n", cnt);
    }
}
