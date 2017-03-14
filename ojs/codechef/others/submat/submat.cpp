#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 102;
int t, n, m;
int mat[N][N];
int res[N][N];
int a;

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &m);

        int ans = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                scanf("%d", &a);
                res[i][j] = min(res[i-1][j], res[i][j-1]) + a;
                ans = max(ans, res[i][j]);
            }
        printf("%d\n", ans);
    }
}
