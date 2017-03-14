#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long num;
num f[100], fs, n, v[20];
        
int main()
{
    int tc;
    f[0] = 0;
    f[1] = 1;
    fs = 1;
    while( f[fs] < 2000000001 )
    {
        f[fs+1] = f[fs] + f[fs-1];
        fs++;
    }
    scanf("%llu", &tc);
    for( int tcn=1; tcn < tc+1; tcn++ )
    {
        scanf("%llu", &n);
        for(int i = 0; i < n; i++)
            scanf("%llu", v+i);
        num ans = 1;
        for( int i = 0; i < n; i++ )
        {
            num local = 0;
            while( v[i] > 0 )
            {
                v[i] -= *(upper_bound(f,f+fs,v[i])-1);
                local++;
            }
            ans *= local;
        }
        printf("Case %llu: %llu\n", tcn, ans);
    }
}
