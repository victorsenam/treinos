#include<bits/stdc++.h>
#define MAX 30002
using namespace std;
typedef int num;
num coins[5] = {1,5,10,25,50},
    sol[5][MAX], n;

num solve(int c, num val )
{
    if( sol[c][val] == -1 )
    {
        if( c > 4 && val != 0 )
            sol[c][val] = 0;
        else if( val == 0 )
            sol[c][val] = 1;
        else
        {
            sol[c][val] = solve(c+1, val);
            if( coins[c] <= val )
                sol[c][val] += solve(c,val-coins[c]);
        }
    }
    return sol[c][val];
}


int main()
{
    memset( sol, -1, sizeof sol );
    while( scanf("%d", &n) != EOF )
        if( solve(0,n) < 2 )
            printf("There is only 1 way to produce %d cents change.\n", n);
        else
            printf("There are %d ways to produce %d cents change.\n", solve(0,n), n);
}
