#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back
const int N = 1e3+7;

int n, m, q[2];
char str[2][N][20];
bool adj[2][N][N];
char eda[20], edb[20];
int siz[2][N];
int s[2][N];
map<string, int> mp[2];

int main () {
    scanf("%d %d %d %d", &n, &m, &q[0], &q[1]);

    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                adj[k][i][j] = !k;
            adj[k][i][i] = 1;
        }

        for (int i = 0; i < n; i++) {
            scanf(" %s", str[k][i]);
            mp[k][str[k][i]] = i;
        }

        for (int i = 0; i < m; i++) {
            scanf(" %s %s", eda, edb);

            int a = mp[k][eda];
            int b = mp[k][edb];
            adj[k][a][b] = adj[k][b][a] = k;
        }

        for (int i =0 ; i <n ; i++)
            for (int j = 0; j < n; j++)
                siz[k][i] += adj[k][i][j];
    }

    int qt[2] = {n,n};

    bool ok = 1;
    while (ok) {
        ok = 0;
        for (int k = 0; k < 2; k++) {
            int a = 0;
            for (int i = 0; i < q[k]; i++)
                if (siz[k][i] > siz[k][a])
                    i = a;


            if (siz[k][a] < qt[k]/2)
                break;

            printf("%c %s\n", 'A'+k, str[k][a]);
            fflush(stdout);

            scanf("%s", edb);
            int b = mp[!k][edb];

            if (b <q[!k]) {
                printf("C Yes\n");
                return 0;
            }

            int i[2] = {a,b};
            for (int z = 0; z < 2; z++) {
                for (int j = 0; j < n; j++) {
                    if (siz[k^z][j] != -1 && adj[k^z][i[z]][j]) {
                        qt[k^z]--;
                        ok = 1;
                        siz[k^z][j] = -1;
                        for (int i = 0; i < n; i++) {
                            if (siz[k^z][i] != -1)
                                siz[k^z][i] -= adj[k^z][j][i];
                        }
                    }
                }
            }
        }
    }
    printf("C No\n");
}
