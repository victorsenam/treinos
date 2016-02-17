#include <cstdio>
using namespace std;
typedef long long num;
const num mod = 1e9+7;
const int N = 502;

num h[N][N], v[N][N], ans;
char grid[N][N];
int h, w;
int q, i0, i1, j0, j1;

int main()
{
    scanf(" %d%d", &h, &w);
    for(int i=1;i<h+1;i++)
        for(int j=1;j<w+1;j++)
            scanf(" %c", &grid[i][j]);

    for(int i=1;i<h+1;i++)
    {
        ans = 0;
        int j = 1;
        while(j <= w)
        {
            num loc = -1;
            while(j <= w && grid[i][j] == '#') j++;
            int last = j;
            while(j <= w && grid[i][j] == '.') loc++, j++;
            for(int jj=last;jj<j;jj++)
                h[i][jj] = ans;
            ans += loc;
        }
    }
    scanf(" %d", &q);
    while(q--)
    {
        scanf( "%d%d%d%d", &i0, &j0, &i1, &j1);
        ans =  (2ll*mod + acc[i1][j1] - acc[i1][j0] - acc[i0][j1] + acc[i0][j0])%mod;
        for(int i=i0+1;i<=i1;i++)
            ans -= (grid[i][j0] == '.' && grid[i][j0+1] == '.');
        for(int j=j0+1;j<=j1;j++)
            ans -= (grid[i0][j] == '.' && grid[i0+1][j] == '.');
        ans %= mod;
        printf("%lld\n", ans);
    }
}
