#include<bits/stdc++.h>
#define MP 2002
using namespace std;
typedef int num;
typedef int point;
num x[MP], y[MP];
num n, ans;

inline int cP( point a, point b, point c )
{ return x[a]*(y[b]-y[c]) + 
         y[a]*(x[c]-x[b]) + 
         x[b]*y[c] - x[c]*y[b] ;}

int main()
{
    scanf("%d", &n);
    for( int i = 0; i < n; i++ )
        scanf("%d %d", x+i, y+i);
    for( int i = 0; i < n; i++ )
        for( int j = i+1; j < n; j++ )
            for( int k = j+1; k < n; k++ )
                if( cP(i,j,k) != 0 )
                    ans++;
    printf("%d\n", ans);
}
