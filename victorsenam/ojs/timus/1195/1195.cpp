// WA

#include <bits/stdc++.h>

using namespace std;

char mat[3][3];
int col[3], row[3], di[2];

int bt (int l) {
    if (l == 0)
        return 0;

    if (l%2) { // X
        int res = -1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (mat[i][j] != '#')
                    continue;
                if (row[i] + 1 == 3 || col[j] + 1 == 3)
                    return 1;
                if (i == j && di[0] + 1 == 3)
                    return 1;
                if (2-i == j && di[1] + 1 == 3)
                    return 1;
                row[i]++;
                col[j]++;
                di[0] += (i==j);
                di[1] += (2-i==j);
                mat[i][j] = 'X';
                res = max(res, bt(l-1));
                if (res == 1)
                    return 1;
                row[i]--;
                col[j]--;
                di[0] -= (i==j);
                di[1] -= (2-i==j);
                mat[i][j] = '#';
            }
        }
        return res;
    } else { // O
        int res = 1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (mat[i][j] != '#')
                    continue;
                if (row[i] - 1 == -3 || col[j] - 1 == -3)
                    return -1;
                if (i == j && di[0] - 1 == -3)
                    return -1;
                if (2-i == j && di[1] - 1 == -3)
                    return -1;
                row[i]--;
                col[j]--;
                di[0] -= (i==j);
                di[1] -= (2-i==j);
                mat[i][j] = 'O';
                res = min(res, bt(l-1));
                if (res == -1)
                    return -1;
                row[i]++;
                col[j]++;
                di[0] += (i==j);
                di[1] += (2-i==j);
                mat[i][j] = '#';
            }
        }
        return res;
    }
}

int main ( ) {
    for (int i = 0; i < 3; i++) {
        scanf("%s", mat[i]);
        for (int j = 0; j < 3; j++) {
            row[i] += mat[i][j]=='#'?0:(mat[i][j]=='X'?1:-1);
            col[j] += mat[i][j]=='#'?0:(mat[i][j]=='X'?1:-1);
            if (i == j)
                di[0] += mat[i][j]=='#'?0:(mat[i][j]=='X'?1:-1);
            else if (2-i == j)
                di[1] += mat[i][j]=='#'?0:(mat[i][j]=='X'?1:-1);
        }
    }

    int res = bt(3);
    if (res == 1)
        printf("Crosses win\n");
    else if (res == -1)
        printf("Ouths win\n");
    else
        printf("Draw\n");
}
