#include<cstdio>
#include<algorithm>
#define MG 101
using namespace std;
typedef int num;
num input[MG][MG], h, w, t;

num solve()
{
    num aux;
    for( int y = h-2; y >= 0; y-- )
        for( int x = 0; x < w; x++ )
        {
            aux = input[y+1][x];
            if( 0 < x   )  aux = max( aux, input[y+1][x-1] );
            if( x < w-1 )  aux = max( aux, input[y+1][x+1] );
            input[y][x] += aux;
        }
    aux = input[0][0];
    for( int i = 1; i < w; i++ )
        aux = max(aux, input[0][i] );
    return aux;
}

int main()
{
    scanf(" %d", &t);
    while( t-- > 0 )
    {
        scanf("%d %d", &h, &w);
        for( int i = 0; i < h; i++ )
            for( int j = 0; j < w; j++ )
                scanf(" %d", &input[i][j] );
        printf("%d\n", solve());
    }
}
