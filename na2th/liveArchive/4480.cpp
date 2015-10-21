#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef int point;
typedef unsigned long long cood;
const int MN = 1000;
cood x[MN], y[MN], dist[MN][MN];
int n, ans, k, pos;

int main()
{
    while( scanf(" %d", &n) && n > 0 )
    {
        memset(dist, 0, sizeof dist);
        ans = 0;
        for(int i=0;i<n;i++)
            scanf(" %llu %llu", x+i, y+i);

        for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            dist[i][j] = dist[j][i] = (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]);

        for(int i=0;i<n;i++)
            sort(&dist[i][0], &dist[i][n]);

        for(int i=0;i<n;i++)
        {
            pos = 1;
            while( pos < n )
            {
                k = 0;
                cood curr = dist[i][pos];
                while( pos < n && dist[i][pos] == curr )
                    pos++, k++;
                ans += k*(k-1)/2;
            }
        }
        printf("%d\n", ans);
    }
}
