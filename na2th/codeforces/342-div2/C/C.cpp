#include <bits/stdc++.h>
using namespace std;
typedef long long num;
const int N = 502;

int n, k;
int ans[N][N], tot;

int main()
{
    scanf(" %d%d", &n, &k);
    for(int j=1;j<k;j++)
        ans[1][j] = j;
    for(int j=k;j<=n;j++)
        ans[1][j] = n*n - n*(n-k+1) + 1 + j-k;

    for(int i=2;i<=n;i++)
        for(int j=1;j<k;j++)
            ans[i][j] = k-1 + ans[i-1][j];

    for(int i=2;i<=n;i++)
        for(int j=k;j<=n;j++)
            ans[i][j] = n - k + 1 + ans[i-1][j];

    for(int i=1;i<=n;i++) tot += ans[i][k];

    printf("%d\n", tot);
    for(int i=1;i<=n;i++,putchar('\n'))
        for(int j=1;j<=n;j++)
            printf("%2d ", ans[i][j]);
}
