#include <bits/stdc++.h>

using namespace std;

const int N = 1007;
const int K = 507;
const int F = 23;

int lim;
int n, k;
int f[N], d[N];
int memo[N*F][N];

/*
int pd(int fun, int sec) {
    if (fun <= 0)
        return 0;
    if (sec >= n)
        return lim+1;

    if (memo[fun][sec] != -1)
        return memo[fun][sec];

    int ra = pd(fun, sec+1);
    if (ra <= lim)
        ra -= k;
    ra = max(0, ra);

    int rb = pd(fun-f[sec], sec+1);
    rb += d[sec];
    rb = min(lim+1, rb);
    
    memo[fun][sec] = min(ra, rb);
    return memo[fun][sec];
}
*/

int main () {
    while (scanf("%d %d %d", &n, &k, &lim) != EOF && n && k && lim) {
        int hi = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d %d", f+i, d+i);
            hi += f[i];
        }
        
        for (int i = 0; i <= hi; i++)
            memo[i][n] = lim+1;
        for (int i = 0; i <= n; i++)
            memo[0][i] = 0;
        
        int i = 1;
        for (i = 1; i <= hi; i++) {
            for (int j = n-1; j >= 0; j--) {
                memo[i][j] = lim+1;
                memo[i][j] = min(memo[i][j], memo[max(0, i-f[j])][j+1] + d[j]);
                if (memo[i][j+1] <= lim)
                    memo[i][j] = min(memo[i][j], max(memo[i][j+1] - k, 0));
            }
            if (memo[i][0] > lim)
                break;
        }

        printf("%d\n", i-1);
    }
}
