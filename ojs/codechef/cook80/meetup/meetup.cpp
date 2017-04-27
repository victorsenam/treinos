#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 2e3+8;

int n, m, q[2];
int mat[2][N][N];
int qtd[2][N];
map<string, int> mp[2];
char nm[2][N][20];
char str[N];
int cur[2];

void fail () {
    printf("C No\n");
    fflush(stdout);
    exit(0);
}

void succ () {
    printf("C Yes\n");
    fflush(stdout);
    exit(0);
}

bool match (char * a, char * b) {
    int i;
    for (i = 0; a[i]; i++)
        if (a[i] != b[i])
            return 0;
    return (a[i] == b[i]);
}

void rem (int k, int u) {
    for (int i = 0; i < n; i++) {
        if (mat[k][u][i]) {
            mat[k][i][u] = 0;
            qtd[k][i]--;
        }
    }
    qtd[k][u] = -1;
}

void query (int k, int i) {
    if (!k) {
        int rm = cur[k] - qtd[k][i];
        if (rm < (cur[k] + 1)/2)
            fail();
    } else {
        int rm = qtd[k][i] + 1;
        if (rm < (cur[k] + 1)/2) 
            fail();
    }

    printf("%c %s\n", 'A'+k, nm[k][i]);
    fflush(stdout);
    scanf(" %s", str);

    for (int j = 0; j < q[!k]; j++) {
        if (match(str, nm[!k][j]))
            succ();
    }

    for (int j = 0; j < q[!k]; j++) {
        if (match(str, nm[!k][j])) {
            for (int u = 0; u < n; u++) {
                if (u != j && mat[k][j][u] == k)
                    rem(k, u);
            }
            rem(k, j);
        }
    }
}

int main () {
    scanf("%d %d %d %d", &n, &m, &q[0], &q[1]);

    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < n; i++) {
            scanf(" %s", nm[k][i]);
            mp[k][nm[k][i]] = i;
        }

        for (int i = 0; i < m; i++) {
            int a, b;
            scanf(" %s", str);
            a = mp[k][str];
            scanf(" %s", str);
            b = mp[k][str];

            mat[k][a][b] = mat[k][b][a] = 1;
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                qtd[k][i] += mat[k][i][j];
    }

    cur[0] = cur[1] = n;

    while (true) {
        int mni = 0;
        for (int i = 0; i < q[0]; i++) {
            if (qtd[0][mni] == -1 || (qtd[0][i] != -1 && qtd[0][mni] > qtd[0][i])) {
                mni = i;
            }
        }

        int mnj = 0;
        for (int i = 0; i < q[1]; i++) {
            if (qtd[1][mnj] < qtd[1][i]) {
                mnj = i;
            }
        }

        if (qtd[0][mni] == -1) {
            if (qtd[1][mnj] == -1) {
                printf("C No\n");
                fflush(stdout);
                return 0;
            }
            
            query(1, mnj);   
        } else if (qtd[1][mnj] == -1) {
            query(0, mni);
        } else {
            if (cur[0] - qtd[0][mni] > qtd[1][mnj] + 1)
                query(0, mni);
            else
                query(1, mnj);
        }
    }
}
