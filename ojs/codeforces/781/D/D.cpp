#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 503;
const int K = 61;
const ll LM = 1000000000000000000;

int n, m;
bitset<N> dest[K][N][2];
bitset<N> orig[K][N][2];

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        a--; b--;

        dest[0][a][c][b] = 1;
        orig[0][b][c][a] = 1;
    }

    ll vl = 1;
    for (int d = 1; d < K; d++) {
        vl *= 2;
        for (int t = 0; t < 2; t++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if ((dest[d-1][i][t] & orig[d-1][j][!t]).any()) {
                        dest[d][i][t][j] = 1;
                        orig[d][j][t][i] = 1;
                    }
                }
            }
        }
    }

    ll res = 0;
    int k = K-1;

    bitset<N> curr;
    for (int i = 0; i < n; i++)
        curr[i] = 1;

    bool t = 0;

    for (int k = K-1; k >= 0; vl /= 2, k--) {
        bitset<N> nw;
        for (int j = 0; j < n; j++) {
            if ((curr & orig[k][j][t]).any())
                nw[j] = 1;
        }

        if (nw.any()) {
            t = !t;
            curr = nw;
            res += vl;
        }
    }

    if (res > LM)
        printf("-1\n");
    else
        printf("%lld\n", res);

}
