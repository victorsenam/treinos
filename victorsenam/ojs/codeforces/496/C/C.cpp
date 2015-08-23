#include <bits/stdc++.h>

using namespace std;

const int N = 107;

char mat[N][N];
int rem[N];
int res;
int m, n;

int isVal(int a, int b, int n) {
    int r = 0;
    for (int i = 0; i < n; i++) {
        if (res > r && rem[r] == i) {
            r++;
            continue;
        }

        if (mat[a][i] > mat[b][i]) {
            return 0;
        }

        if (mat[a][i] < mat[b][i])
            break;
    }
    return 1;
}

int main () {
    scanf("%d %d", &m, &n);

    for (int i = 0; i < m; i++)
        scanf(" %s", mat[i]);

    res = 0;
    for (int k = 0; k < n; k++) {
        for (int i = 1; i < m; i++) {
            if (!isVal(i-1, i, k+1)) {
                rem[res++] = k;
                break;
            }
        }
    }

    printf("%d\n", res);
}
