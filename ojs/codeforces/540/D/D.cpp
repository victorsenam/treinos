#include <bits/stdc++.h>

using namespace std;

#define N 101

typedef unsigned long long int num;
double mr[N][N][N];
double mp[N][N][N];
double ms[N][N][N];

void pd (int r, int p, int s) {
    if (mr[r][p][s] != 2.0) return;
    mr[r][p][s] = 0.0;
    mp[r][p][s] = 0.0;
    ms[r][p][s] = 0.0;

    if (!r) ms[r][p][s] = 1;
    if (!p) mr[r][p][s] = 1;
    if (!s) mp[r][p][s] = 1;
    if (r && p && s) {
        pd(r-1, p, s);
        pd(r, p-1, s);
        pd(r, p, s-1);

        mr[r][p][s] = (r*p*mr[r-1][p][s] + s*p*mr[r][p-1][s] + r*s*mr[r][p][s-1])/(r*p+r*s+s*p);
        mp[r][p][s] = (r*p*mp[r-1][p][s] + s*p*mp[r][p-1][s] + r*s*mp[r][p][s-1])/(r*p+r*s+s*p);
        ms[r][p][s] = (r*p*ms[r-1][p][s] + s*p*ms[r][p-1][s] + r*s*ms[r][p][s-1])/(r*p+r*s+s*p);
    }
}

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &c, &b);

    for (int i = 0; i <= a; i++) {
        for (int j = 0; j <= b; j++) {
            for (int k = 0; k <= c; k++) {
                mr[i][j][k] = mp[i][j][k] = ms[i][j][k] = 2.0;
            }
        }
    }

    pd(a, b, c);

    printf("%1.12f ", mr[a][b][c]);
    printf("%1.12f ", ms[a][b][c]);
    printf("%1.12f\n", mp[a][b][c]);
}

