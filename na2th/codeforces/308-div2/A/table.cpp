#include<cstdio>
#define MAX 102
using namespace std;
typedef int num;

num grid[MAX][MAX];
num n, x1, y1, x2, y2;

int main()
{
    scanf("%d", &n);
    for( int i = 0; i < MAX*MAX; i++ )
        grid[i/MAX][i%MAX] = 0;

    while( n-- > 0 )
    {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        for( num x = x1; x <= x2; x++ )
            for( num y = y1; y <= y2; y++ )
                grid[x][y]++;
    }
    num ans = 0;
    for( int i = 0; i < MAX*MAX; i++ )
        ans += grid[i/MAX][i%MAX];
    printf("%d\n", ans);
}
