#include<bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
const int MN = 101;
const int MK = 101;
struct mod
{
    int x;
    mod () : x(0) {}
    mod (int a) : x(a) {}
    mod operator+(mod b) { return ((long long)x+(long long)b.x)%MOD; }
    mod operator*(mod b) { return ((long long)x*(long long)b.x)%MOD; }
} sol[MN][MK], comb[MN][MN];
int seen[MN][MK];
int n, k, tc;

mod solve(int n, int k)
{
    if( n == 0 ) return (k<=::k);
    if( k >= ::k ) return 0;
    if( seen[n][k] != tc )
    {
        sol[n][k] = 0;
        for(int j=1;j<n+1;j++)
            sol[n][k] = sol[n][k] + mod(j)*comb[n-1][j-1]*solve(j-1,1)*solve(n-j,k+1);
        seen[n][k] = tc;
    }
    return sol[n][k];
}

int main()
{
    for(int i=0;i<MN;i++) comb[i][0] = 1;
    for(int i=1;i<MN;i++)
        for(int j=1;j<MN;j++)
            comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
    while( scanf("%d %d", &n, &k) != EOF )
    {
        tc++;
        printf("%d\n", solve(n-1,0));
    }
}
