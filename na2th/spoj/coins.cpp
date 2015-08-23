#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long num;
map<num, num> sol;
num in;

num solve( num m )
{
    if( sol.count(m) == 0 )
        sol[m] = max( m, solve(m/2) + solve(m/3) + solve(m/4) );
    return sol[m];
}

int main()
{
    sol[0] = 0;
    sol[1] = 1;
    sol[2] = 2;
    while( scanf("%llu", &in) > 0 )
        printf("%llu\n", solve(in));
}
