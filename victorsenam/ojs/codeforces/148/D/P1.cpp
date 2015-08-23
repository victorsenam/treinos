#include <bits/stdc++.h>

using namespace std;

#define N 1001

typedef double num;

double memo[N][N][2];

double pd (int x, int y, bool t) {
    if (memo[x][y][t] != 2.0) return memo[x][y][t];

    double w = x;
    double b = y;

    if (!t) {
        if (w && !b) memo[x][y][t] = 1;
        else if (!w) memo[x][y][t] = 0;
        else memo[x][y][t] = (w + b*pd(x, y-1, !t))/(w+b);
    } else {
        if (w && !b) memo[x][y][t] = 0;
        else if (w && b==1) memo[x][y][t] = pd(x-1, 0, 0)/(w+1);
        else if (!w && b) memo[x][y][t] = 1;
        else memo[x][y][t] = (b/(w+b))*(((b-1)/(w+b-1))*pd(x,y-2,0) + (w/(w+b-1))*pd(x-1,y-1,0));
    }


    return memo[x][y][t];
}

int main () {
    int a, c;
    scanf("%d %d", &a, &c);

    for (int i = 0; i <= a; i++)
        for (int j = 0; j <= c; j++)
            memo[i][j][0] = memo[i][j][1] = 2.0;

    printf("%1.9f\n", pd(a, c, 0));
}
