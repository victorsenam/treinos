#include<bits/stdc++.h>
#define N 1025
typedef int num;
using namespace std;
char cmd[4];
num t;

struct BIT
{
    num freq[N][N], n;
    void set()
    {
        for(int i = 0; i < n*n; i++ )
            freq[i/n][i%n] = 0;
    }
    void insert( int xin, int yin, num val )
    {
        for( int x = xin; x <= n; x += (x&-x) )
            for( int y = yin; y <= n; y += (y&-y) )
                freq[x][y] += val;
    }
    num count( int xin, int yin )
    {
        num sum = 0;
        for( int x = xin; x > 0; x -= (x&-x) )
            for( int y = yin; y > 0; y -= (y&-y) )
                sum += freq[x][y];
        return sum;
    }
    inline num sCount( int xin, int yin )
    {
        return count(xin, yin) - count(xin,yin-1) - count(xin-1,yin) + count(xin-1,yin-1);
    }
} tree;

int main()
{
    scanf("%d", &t);
    while( t-- > 0 )
    {
        num x1, x2, y1, y2, val;
        scanf("%d", &tree.n);
        tree.n++;
        tree.set();
        while ( scanf(" %s", cmd) )
        {
            if( cmd[1] == 'E' ) // SET
            {
                scanf("%d %d %d", &x1, &y1, &val);
                x1++; y1++;
                num q = tree.sCount(x1, y1);
                tree.insert(x1,y1,val-q);
            }
            else if( cmd[1] == 'U' ) // SUM
            {
                scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                x2++;y2++;
                printf("%d\n", tree.count(x2,y2) 
                        - tree.count(x2, y1) - tree.count(x1,y2)
                        + tree.count(x1,y1));
            }
            else
                break;
        }
        printf("\n");
    }
}
