#include <cstdio>

using namespace std;

int main()
{
    int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1},
        dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1},
        n, m, check, grid[1000][1000];

        while( scanf("%d %d", &n, &m) != EOF )
        {
            for( int i = 0; i < n*m ; i++ )
                scanf("%d", &grid[i/m][i%m]);

            for(int i = 0; i < n ; i++ )
                for(int j = 0; j < m; j++) {
                    int pico = 1;
                    for(int move = 0; move < 8 && pico ; move++ )
                    {
                        if( ( i + dy[move] >= 0 ) && ( i + dy[move] < n ) && ( j + dx[move] >= 0 ) && (  j + dx[move] < m ) )
                            pico &= (grid[i][j] > grid[i + dy[move]][j + dx[move]]);
                    }
                    if(pico)
                        printf("%d %d\n", i + 1, j + 1); 
                }

        }
}
