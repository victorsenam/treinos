#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

const int N = 1007;
const int K = 107;
const num MOD = 1000000007;
const num B = 263;

int n, m, k;
int vis[N][N][2];
int memo[N][N][2];
num hash[2][N];
int turn;
char str[2][N];

inline num mod (num a) {
    return (a%MOD + MOD)%MOD;
}

int pd (int i, int j, bool free) {
    if (!free) {
        if (i > n-k || j > m-k)
            return 0;
    } else {
        if (i == n || j == m)
            return 0;
    }

    int & me = memo[i][j][free];
    if (vis[i][j][free] == turn)
        return me;

    me = 0;
    vis[i][j][free] = turn;
    me = max(pd(i+1, j, 0), me);
    me = max(pd(i, j+1, 0), me);

    if (free) {
        if (str[0][i] == str[1][j])
            me = max(me, pd(i+1, j+1, 1) + 1);
    } else {
        if (hash[0][i] == hash[1][j])
            me = max(me, pd(i+k, j+k, 1) + k);
    }
    
    return me;
}

int main () {
    while (scanf("%d", &k) != EOF && k) {
        turn++;
        scanf(" %s %s", str[0], str[1]);
        n = strlen(str[0]);
        m = strlen(str[1]);
        
        if (n < k || m < k) {
            printf("0\n");
            continue;
        }
        
        for (int i = 0; i <= n-k; i++) {
            hash[0][i] = 0;
            for (int l = 0; l < k; l++) 
                hash[0][i] = ((hash[0][i]*B)%MOD + ((num)str[0][i+l]))%MOD;
        }

        for (int i = 0; i <= m-k; i++) {
            hash[1][i] = 0;
            for (int l = 0; l < k; l++)
                hash[1][i] = ((hash[1][i]*B)%MOD + ((num)str[1][i+l]))%MOD;
        }

/*
        for (int i = 0; i <= n-k; i++) {
            for (int l = 0; l < k; l++)
                printf("%c", str[0][i+l]);
            printf(": %llu\n", hash[0][i]);
        }
        printf("\n");

        for (int i = 0; i <= m-k; i++) {
            for (int l = 0; l < k; l++)
                printf("%c", str[1][i+l]);
            printf(": %llu\n", hash[1][i]);
        }
*/

        printf("%d\n", pd(0, 0, 0));
    }
}
