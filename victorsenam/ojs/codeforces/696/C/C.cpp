#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const ll mod = 1e9+7;

ll ini[4][4] = {
    {2, mod-1},
    {0, mod-1},
};

ll mat[4][4][4];

inline void mult (int a, int b) {
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++) {
            mat[2][i][j] = 0;
            for (int k = 0; k < 2; k++)
                mat[2][i][j] += mat[a][i][k]*mat[b][k][j];
        }


    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            mat[a][i][j] = mat[2][i][j]%mod;
}

int main () {
    int k;
    ll e;
    ll q = 2;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            mat[0][i][j] = ini[i][j];

    scanf("%d", &k);
    while (k--) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                mat[1][i][j] = (i == j);
            }
        }
        ll r = 1;

        scanf("%I64d", &e);
        while (e) {
            if (e&1) {
                mult(1, 0);
                r = (r*q)%mod;
            }
            mult(0, 0);
            q = (q*q)%mod;
            e >>= 1;
        }

        q = r;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                mat[0][i][j] = mat[1][i][j];
    }

    ll rr = ((( ((mod+1)/2)*mat[1][0][0] )%mod + mat[1][0][1]))%mod;
    printf("%d/%d\n", int(rr), int((q*(mod+1)/2)%mod));
}
