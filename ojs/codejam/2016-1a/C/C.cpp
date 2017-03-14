#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 1007;

int visi[N];
int best[N];
int next[N];
int ts;
int n;
int ls;

int dfs (int i, int f) {
    if (visi[i] == f) {
        if (next[i] == ls) {
            return 1;
        }
        if (i == f) {
            ls = f;
            return 1;
        }
        return 0;
    }
    visi[i] = f;

    ls = i;
    
    int ret = dfs(next[i], f);
    if (ret)
        return ret+1;
    return 0;
}

int main () {
    scanf("%d", &ts);
    for (int t = 1; t <= ts; t++) {
        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            scanf("%d", next+i);
            next[i]--;
            best[i] = 0;
            visi[i] = -1;
        }
        int ans = 0;

        for (int i = 0; i < n; i++) {
            ls = -1;
            int ret = dfs(i, i);
            if (ret) {
                ret--;
   //             DEBUG("%d->%d : %d\n", i+1, ls+1, ret);
                if (ls == i) {
                    ans = max(ans, ret);
                } else {
                    best[ls] = max(best[ls], ret);
                }
            }
        }

        int sum = 0;
        for (int i = 0; i < n; i++) {
            if (i > next[i] && next[next[i]] == i) {
                sum += best[i] + best[next[i]] - 2;
 //               DEBUG("(%d,%d) : %d + %d - 2\n", next[i]+1, i+1, best[next[i]], best[i]);
            }
        }
        ans = max(ans, sum);
        printf("Case #%d: %d\n", t, ans);
    }
}
