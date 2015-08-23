#include<cstdio>
#include<cctype>
#include<cstring>
#define GM 200
typedef int num;
num in[GM][GM], out[GM][GM], Q[GM*GM], qf, qb;
num dx[4] = { -1,  0,  1,  0},
    dy[4] = {  0,  1,  0, -1};
num t, n, m;

int main()
{
    scanf("%d", &t);
    while( t-- > 0 )
    {
        qf = qb = 0;
        scanf(" %d %d", &n, &m);
        for( int i = 0; i < n; i++ )
            for( int j = 0; j < m; j++ )
            {
                scanf("%c", &in[i][j]);
                out[i][j] = -1;
                if( isspace(in[i][j]) ) j--;
                else if ( in[i][j] == '1' )
                {
                    Q[qb++] = i*m + j;
                    out[i][j]++;
                }
            }
        while( qf < qb )
        {
            num x = Q[qf]/m,
                y = Q[qf++]%m;
            for( int i = 0; i < 4; i++ )
                if( 0 <= x + dx[i] && x + dx[i] < n && 0 <= y + dy[i] && y + dy[i] < m && out[x+dx[i]][y+dy[i]] == -1 )
                {
                    out[x+dx[i]][y+dy[i]] = out[x][y] + 1;
                    Q[qb++] = (x+dx[i])*m + y+dy[i];
                }
        }
        for( int i = 0; i < n; i++ )
        {
            for( int j = 0; j < m; j++ )
                printf("%d ", out[i][j]);
            printf("\n");
        }
    }
}
