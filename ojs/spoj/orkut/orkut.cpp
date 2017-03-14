#include <bits/stdc++.h>

using namespace std;

#define N 30

bool mat[N][N];
int c[N], a, b, t, n, m, k;
string s[N];
map<string, int> h;
char temp[17];
int ord[N];

int main () {
    t = 0;
    while (scanf("%d", &n) != EOF && n) {
        h.clear();

        for (int i = 0; i < n; i++) {
            scanf(" %s", temp);
            s[i] = temp;
            c[i] = 0;
            h.insert(make_pair(s[i], i));
            for (int j = 0; j < n; j++) mat[i][j] = 0;
        }

        for (int i = 0; i < n; i++) {
            scanf(" %s", temp);
            a = h.find(temp)->second;

            scanf(" %d", &m);
            for (int j = 0; j < m; j++) {
                scanf(" %s", temp);
                b = h.find(temp)->second;

                mat[a][b] = 1;
                c[a]++;
            }
        }

        for (k = 0; k < n; k++) {
            for (a = 0; a < n && c[a]; a++);
            if (a == n) break;

            for (int i = 0; i < n; i++) {
                if (mat[i][a]) {
                    mat[i][a] = 0;
                    c[i]--;                }
            }
            c[a]--;

            ord[k] = a;
        }

        printf("Teste %d\n", ++t);
        if (k < n) printf("impossivel");
        else {
            for (int i = 0; i < k; i++) printf("%s ", s[ord[i]].c_str());
        }
        printf("\n\n");
    }
}
