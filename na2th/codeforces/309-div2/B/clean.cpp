#include <bits/stdc++.h>
#define MG 101
using namespace std;
typedef int num;
char grid[MG][MG];
num n, ans, guess;

int main()
{
    scanf("%d ", &n);
    for( int i = 0; i < n*n; i++ )
    {
        scanf("%c", &grid[i/n][i%n]);
        if( isspace(grid[i/n][i%n]) ) i--;
    }

    for( int i = 0; i < n; i++ )
    {
        guess = 1;
        for( int j = i+1; j < n; j++ )
        {
            bool same = true;
            for( int k = 0; same && k < n; k++ )
                same = ( grid[i][k] == grid[j][k] );
            if( same ) guess++;
        }
        ans = max( ans, guess );
    }
    printf("%d\n", ans);
}
