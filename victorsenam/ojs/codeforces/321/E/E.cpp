#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 4002;

int n, k, q;
char str[N][N];
char aux[2*N];
num acc[N][N];
num dp[2][N];

inline num cost (int i, int j) 
{ return acc[j+1][j+1] + acc[i+1][i+1] - acc[i+1][j+1] - acc[j+1][i+1]; }

inline num calc (int i, int j, bool ty)
{ return dp[!ty][j] + cost(j, i); }

void solve (int i, int j, int l, int r, bool ty) {
    if (i == j)
        return;

    int mid = i + ((j-i)>>1);
    
    int ir = min(r, mid);

    int maxi = l;
    num mval = INT_MAX;

    for (int k = l; k < ir; k++) {
        num loc = calc(mid, k, ty);
        if (loc < mval) {
            maxi = k;
            mval = loc;
        }
    }
    dp[ty][mid] = mval;
    
    solve(i, mid, l, maxi+1, ty);
    solve(mid+1, j, maxi, r, ty);
}

int main () {
    scanf("%d %d", &n, &k);

    acc[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        acc[i][0] = acc[0][i] = 0;
        scanf(" %[0-9 ]", aux);
        for (int j = 1; j <= n; j++)
            str[i][j] = aux[((j-1)<<1)]-'0';
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            acc[i][j] = acc[i-1][j] + acc[i][j-1] - acc[i-1][j-1] + str[i][j];

    for (int i = 0; i < n; i++)
        dp[1][i] = cost(-1, i);

/*
    for (int i = 0; i < n; i++)
        printf("%I64d ", dp[1][i]);
    printf("\n");
*/
    
    for (int q = 2; q <= k; q++) {
        solve(0, n, 0, n, q&1);
        /*
        for (int i = 0; i < n; i++)
            printf("%I64d ", dp[q&1][i]);
        printf("\n");
        */
    }
        
     //           dp[t][i] = dp[!t][q-1] + cost(q-1, i);
            
     //           dp[t][i] = min(dp[t][i], dp[!t][j] + cost(j, i));

    printf("%I64d\n", (dp[k&1][n-1]>>1));
}
