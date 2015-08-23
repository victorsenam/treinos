#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef long long ll;
const int N = 1002;
num x[N], y[N], ds, ans, n;
ll dist[N*N];

int main()
{
    int tc;
    scanf("%d", &tc);
    for(int tcn=1;tcn<tc+1; tcn++)
    {
        scanf("%d", &n);
        ds = 0;
        for(int i=0;i<n;i++)
            scanf("%d %d", x+i, y+i);
        dist[ds++] = 0;
        for(int i=0;i<n;i++)
            for(int j=i+1;j<n;j++)
                dist[ds++] = 1ll*(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);

        sort(dist, dist+ds);
        ans = 0;
        int p = 0, lp = 0;
        while( p < ds )
        {
            ans++;
            while( dist[p] == dist[lp] ) p++;
            lp = p;
        }
        printf("Case %d: %d\n", tcn, ans);
    }
}
