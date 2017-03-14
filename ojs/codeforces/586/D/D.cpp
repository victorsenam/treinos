#include <bits/stdc++.h>

using namespace std;

const int N = 102;
const int M = 3;

int n, k;
int s;
bool memo[M][N];
int visi[M][N];
char mat[M][N];
int turn;
int t;

bool pd (int y, int x) {
    if (x >= n)
        return 1;
    if (y < 0 || y >= 3 || mat[y][x] != '.')
        return 0;

    if (visi[y][x] == turn)
        return memo[y][x];
    visi[y][x] = turn;
    
    if (x + 1 >= n)
        return memo[y][x] = 1;
    if (mat[y][x+1] != '.')
        return memo[y][x] = 0;

    for (int j = -1; j <= 1; j++) {
        bool ok = 1;
        if (y+j < 0 || y+j >= 3)
            continue;
        for (int i = 1; i <= 3 && ok; i++) {
            if (x + i < n && mat[y+j][x+i] != '.')
                ok = 0;
        }

        if (ok && pd(y+j, x+3))
            return memo[y][x] = 1;
    }
    return memo[y][x] = 0;
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &k);

        for (int j = 0; j < 3; j++) {
            scanf(" %s", mat[j]);
            if (mat[j][0] == 's')
                s = j;
        }
        mat[s][0] = '.';

        turn++;
        if (pd(s, 0))
            printf("YES\n");
        else
            printf("NO\n");
    }
}
