#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e3+7;
const ll MOD = 1e9+7;

ll pd[N][N][2];
int t, n;

int main () {

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int b = 0; b < 2; b++) {
                if (i == 0) {
                    pd[i][j][b] = b;
                } else {
                    pd[i][j][b] = 0;
                    if (i - j >= 0)
                        pd[i][j][b] = (pd[i][j][b] + pd[i-j][j][!b])%MOD;
                    if (j > 0)
                        pd[i][j][b] = (pd[i][j][b] + pd[i][j-1][b])%MOD;
                }
            }
        }
    }

    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        scanf("%d", &n);
        printf("%lld\n", pd[n][n][n%2]);
    }

}
