#include<bits/stdc++.h>
#include <bits/stdc++.h>
using namespace std;
typedef int num;
const int MOD = 1000000;
num mem[1001];

num fact(num x)
{
    num ans = 1;
    for(int i = 2; i < x+1; i++)
        ans = (ans*i)%MOD;
    return ans%MOD;
}

num solve(num x)
{
    if( x == 3 ) return 5;
    if( x < 3 ) return fact(x);
    if( mem[x] == -1 )
    {
        num ans = 0,
            big = fact(x-1);
        for(int i = 0; i < x-1; i++)
                ans = (ans + (((big/fact(x-1-i))%MOD)*solve(x-i-1))%MOD)%MOD;
        mem[x] = ans%MOD;
    }
    return mem[x];
}

int main()
{
    num n;
    memset(mem, -1, sizeof mem);
    while( scanf("%d",&n) && n > 0 )
        printf("%d\n", solve(n)%MOD);
}
