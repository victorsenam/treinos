#include <bits/stdc++.h>

using namespace std;

int n, nx, x[10], siz;
int memo[10][10][2][2];
int visi[10][10][2][2];
int turn;
int res[10];

int pd (int dig, int pos, bool free, bool lz) {
    if (pos == -1) 
        return 0;

    int & m = memo[dig][pos][free][lz];
    if (visi[dig][pos][free][lz] == turn)
        return memo[dig][pos][free][lz];
    visi[dig][pos][free][lz] = turn;

    int mul = 1;
    for (int i = 0; i < pos; i++)
        mul *= 10;
    int x = (n/mul)%10;

    if (free) {
        if (dig || lz)
            m = 10*pd(dig, pos-1, free, lz) + mul;
        else
            m = 9*pd(dig, pos-1, free, 1) + pd(dig, pos-1, free, 0);
    } else if (x) {
        if (dig || lz)
            m = x*pd(dig, pos-1, 1, lz) + pd(dig, pos-1, 0, lz) + mul*(x>dig) + (n%mul+1)*(x==dig);
        else
            m = (x-1)*pd(dig, pos-1, 1, 1) + pd(dig, pos-1, 0, 1) + pd(dig, pos-1, 1, 0);
    } else {
        m = pd(dig, pos-1, 0, lz);
        if (!dig && lz)
            m += n%mul+1;
    }

    return m;
}

int main () {
    turn = 1;
    while (scanf("%d %d", &n, &nx) != EOF && (n || nx)) {
        n--;
        for (int i = 0; i < 10; i++) {
            res[i] = pd(i, 9, 0, 0);
        }
        turn++;
        
        n = nx;
        for (int i = 0; i < 9; i++)
            printf("%d ", pd(i, 9, 0, 0) - res[i]);
        printf("%d\n", pd(9, 9, 0, 0) - res[9]);
        turn++;
    }
}
