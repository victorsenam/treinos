#include <bits/stdc++.h>

using namespace std;

const int N = 1007;

int n;
char mat[2][N];
int visi[N][3][3];
int memo[N][3][3];
int turn;

int pd (int i, int up, int dw) {
    if (i == n) {
        if (up == 1 || dw == 1)
            return 4000;
        return 0;
    }

    if (mat[0][i] == 'X') {
        if (up == 1)
            return 4000;
        else
            up = 0;
    }
    if (mat[1][i] == 'X') {
        if (dw == 1)
            return 4000;
        else
            dw = 0;
    }

    int & me = memo[i][up][dw];
    if (visi[i][up][dw] == turn)
        return me;
    visi[i][up][dw] = turn;
    me = 4000;

    if (mat[0][i] != 'X')
        me = min(me, pd(i+1, 2, dw) + 1);
    if (mat[1][i] != 'X')
        me = min(me, pd(i+1, up, 2) + 1);
    if (mat[0][i] != 'X' && mat[1][i] != 'X')
        me = min(me, pd(i+1, 2, 2) + 2);

    if (up == 0 && mat[0][i] != 'X')
        up = 1;
    if (dw == 0 && mat[1][i] != 'X')
        dw = 1;
    me = min(me, pd(i+1, up, dw));

    return me;
}

void mount(int i, int up, int dw) {
    if (i == n) {
        printf("end\n");
        return;
    }

    printf("(%d,%d,%d) -> %d\n", i, up, dw, pd(i, up, dw));
    if (mat[0][i] != 'X' && pd(i, up, dw) == pd(i+1, 2, dw) + 1)
        mount(i+1, 2, dw);
    else if (mat[1][i] != 'X' && pd(i, up, dw) == pd(i+1, up, 2) + 1)
        mount(i+1, up, 2);
    else if (mat[0][i] != 'X' && mat[1][i] != 'X' && pd(i, up, dw) == pd(i+1,2,2)+2)
        mount(i+1, 2, 2);
    else {
        int nu = up;
        if (mat[0][i] == 'X')
            nu = 0;
        else if (up == 0)
            nu = 1;
        int nd = dw;
        if (mat[1][i] == 'X')
            nd = 0;
        else if (dw == 0)
            nd = 1;
        mount(i+1, nu, nd);
    }
}

int main () {
    int t;
    scanf("%d", &t);
    for (int c = 1; c <= t; c++) {
        scanf("%d", &n);
        turn++;
        scanf(" %s %s", &mat[0], &mat[1]);
        printf("Case #%d: %d\n", c, pd(0, 0, 0));
        //mount(0,0,0);
    }
}
