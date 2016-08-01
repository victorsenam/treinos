#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 3;
const double pi = acos(-1.);

double mat[3][N][N];
int t;
double a, l;
int n;

void mult (int a, int b) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            mat[2][i][j] = 0.;
            for (int k = 0; k < N; k++)
                mat[2][i][j] += mat[a][i][k]*mat[b][k][j];
        }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            mat[a][i][j] = mat[2][i][j];
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%lf %lf %d", &a, &l, &n);

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                mat[0][i][j] = (i == j);

        mat[1][0][0] = mat[1][1][1] = cos(a*pi/180.);
        mat[1][0][1] = -(mat[1][1][0] = sin(a*pi/180.));
        mat[1][0][2] = l;
        mat[1][2][0] = mat[1][2][1] = mat[1][1][2] = 0.;
        mat[1][2][2] = 1.;

        while (n) {
            if (n&1) mult(0, 1);
            mult(1, 1);
            n >>= 1;
        }

        printf("%.20f %.20f\n", mat[0][0][2], mat[0][1][2]);
    }
}
