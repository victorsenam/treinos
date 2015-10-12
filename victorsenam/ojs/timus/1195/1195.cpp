#include <bits/stdc++.h>

using namespace std;

char mat[3][3];

inline int val (char c) {
    if (c == 'X')
        return 1;
    else if (c == 'O')
        return -1;
    else
        return 0;
}

inline int calc (int v) {
    if (v == -3)
        return -1;
    else if (v == 3)
        return 1;
    else
        return 0;
}

int minimax (int l) {
    if (l == -1)
        return 0;
    int part;
    int res = 0;

    int dia = 0;
    int dib = 0;
    for (int i = 0; !res && i < 3; i++) {
        int row = 0;
        int col = 0;
        dia += val(mat[i][i]);
        dib += val(mat[2-i][i]);
        for (int j = 0; j < 3; j++) {
            row += val(mat[i][j]);
            col += val(mat[j][i]);
        }
        if (calc(row))
            res = calc(row);
        if (calc(col))
            res = calc(col);
    }

    if (res);
    else if (calc(dia))
        res = calc(dia);
    else if (calc(dib))
        res = calc(dib);
    else if (l == 0)
        res = 0;
    else {
        res = l%2?-1:1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (mat[i][j] != '#')
                    continue;
                if (l%2) {
                    mat[i][j] = 'X';
                    res = max(minimax(l-1), res);
                } else {
                    mat[i][j] = 'O';
                    res = min(minimax(l-1), res);
                }
                mat[i][j] = '#';
            }
        }
    }

/*
    printf("%d -> %d\n", l,  res);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            printf("%c", mat[i][j]);
        printf("\n");
    }
    printf("\n");
*/
    return res;
}

int main () {
    for (int i = 0; i < 3; i++)
        scanf(" %s", mat[i]);

    int res = minimax(3);
    if (res == 1)
        printf("Crosses win\n");
    else if (res == -1)
        printf("Ouths win\n");
    else
        printf("Draw\n");
}
