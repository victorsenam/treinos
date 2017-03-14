#include <bits/stdc++.h>

using namespace std;

const int K = 27;
const int N = 204;

int k, n;
int mp[256];
int memo[N][N][K];
int visi[N][N];

char res[K][K];
int tim[K][K];
int turn;
char sy[N];
char str[N];

void solve (int i, int j) {
    if (visi[i][j] == turn)
        return;

    visi[i][j] = turn;
    for (int l = 0; l < k; l++)
        memo[i][j][l] = INT_MAX;

    if (i == j) {
        memo[i][j][mp[str[i]]] = 0;
        return;
    }

    for (int l = i; l < j; l++) {
        solve(i, l); solve(l+1, j);
        for (int a = 0; a < k; a++) {
            for (int b = 0; b < k; b++) {
                int & g = memo[i][j][mp[res[a][b]]];
                if (memo[i][l][a] == INT_MAX)
                    continue;
                if (memo[l+1][j][b] == INT_MAX)
                    continue;

                g = min(g, memo[i][l][a]+memo[l+1][j][b]+tim[a][b]);
            }
        }
    }
}

int main () {
    int ts = 0;
    while (scanf("%d", &k) != EOF && k) {
        if (ts++) printf("\n");
        for (int i = 0; i < k; i++) {
            scanf(" %c", sy+i);
            mp[sy[i]] = i;
        }

        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                scanf("%d-%c", &tim[i][j], &res[i][j]);
            }
        }

        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            turn++;
            scanf(" %s", str);   
            int s = strlen(str)-1;
            solve(0, s);
            int best = min_element(memo[0][s], memo[0][s] + k) - memo[0][s];

            printf("%d-%c\n", memo[0][s][best], sy[best]);
        }
    }
}
