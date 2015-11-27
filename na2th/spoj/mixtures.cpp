#include <bits/stdc++.h>
using namespace std;
typedef long long num;

const int MN = 101;

num sol[MN][MN], res[MN][MN], in[MN];
int n;

int main()
{
    while( scanf(" %d", &n) != EOF )
    {
        for(int i=0;i<n;i++)
            scanf(" %lld", in+i);

        for(int i=0;i<n;i++)
            sol[i][i+1] = 0, res[i][i+1] = in[i];

        for(int t=2;t<n+1;t++)
            for(int i=0;i+t<n+1;i++)
            {
                sol[i][i+t] = 1e9;
                res[i][i+t] = (res[i][i+1]+res[i+1][i+t])%100;
                for(int k=i;k<i+t;k++)
                    sol[i][i+t] = min(sol[i][i+t], 
                    sol[i][k] + sol[k][i+t] + res[i][k]*res[k][i+t]);
            }

        printf("%lld\n", sol[0][n]);
    }
}
