#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int K = 6;
const int N = 1e3+3;
const int mv[4][2] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
};
const char lt[] = "DRUL";
const char ty[] = "#12345";

short memo[N][N][K][4];
char mat[N][N];
int dr[N][2];
char str[N];
int n, m, k, siz;

bool isval (int i, int j) {
    if (i < 0 || i >= n || j < 0 || j >= m) return 0;
    return 1;
}

short pd (int i, int j, int t, int k) {
    if (!isval(i, j)) return 0;

    short & me = memo[i][j][t][k];
    if (me != -1) return me;
    
    if (mat[i][j] == ty[t]) me = 0;
    else me = pd(i+mv[k][0], j+mv[k][1], t, k) + 1;

    return me;
}

short pd (int i, int j, int t, int k, bool art) {
    i += mv[k][0];
    j += mv[k][1];
    return pd(i, j, t, k) + 1;
}

bool solve (int i, int j) {
    int p = 0;

    i -= mv[dr[0][0]][0];
    j -= mv[dr[0][0]][1];

    for (int r = 0; r < k; r++) {
        int q = dr[r][1];
        int d = dr[r][0];
        int fl = pd(i, j, 0, d, 1);

        if (fl <= q) return 0;

        while (q) {
            int nx;
            if (p == siz) {
                nx = q;
            } else {
                nx = pd(i, j, str[p]-'0', d, 1);

                if (nx <= q) {
                    p++;
                } else {
                    nx = q;
                }
            }

            i += mv[d][0]*nx;
            j += mv[d][1]*nx;
            q -= nx;
        }
    }

    if (p == siz) 
        return 1;
    return 0;
}

int main () {
    memset(memo, -1, sizeof memo);
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
        scanf(" %s", mat[i]);
    
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        char c;
        scanf(" %c %d", &c, &dr[i][1]);
        for (dr[i][0] = 0; lt[dr[i][0]] != c; dr[i][0]++);
    }
    dr[0][1]++;

    scanf(" %s", str);
    siz = strlen(str);

    int res = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (solve(i, j)) {
                res++;
            }
        }

    printf("%d\n", res);
}
