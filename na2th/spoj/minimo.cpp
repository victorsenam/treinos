#include<bits/stdc++.h>
#define MV 105
using namespace std;
typedef int num;
num dist[MV][MV][MV+1];
num n, m, t, c;

int main()
{
    int tc = 1;
    while( scanf("%d %d", &n, &m) != EOF )
    {
        printf("Instancia %d\n", tc++);
        for( int i = 0; i < n; i++ )
            for( int j = 0; j < n; j++ )
                dist[i][j][0] = (i == j) ? 0 : INT_MAX;
        for( int i = 0; i < m; i++ )
        {
            num u, v, w;
            scanf("%d %d %d", &u, &v, &w); u--;v--;
            dist[u][v][0] = min( dist[u][v][0], w );
        }
        scanf("%d", &c);

        for( int k = 0; k < n; k++ )
            for( int i = 0; i < n; i++ )
                for( int j = 0; j < n; j++ )
                    dist[i][j][k+1] = min( 1LL*dist[i][j][k], 1ll*dist[i][k][k] + dist[k][j][k] );

        while( c-- > 0 )
        {
            num u,v,t;
            scanf("%d %d %d", &u, &v, &t);
            if( dist[u-1][v-1][t] < INT_MAX )
                printf("%d\n", dist[u-1][v-1][t]);
            else
                printf("-1\n");
        }
        printf("\n");
    }
}
