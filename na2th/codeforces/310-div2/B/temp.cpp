#include <bits/stdc++.h>
using namespace std;
typedef int num;
const num MN = 1000;
num a[MN], n;
bool ok;

int main()
{
    scanf("%d", &n);
    for( int i = 0; i < n; i++ )
        scanf("%d", a+i);
    ok = false;
    for( int i = 0; !ok && i < n; i++ )
    {
        ok = (a[0] == 0);
        for( int j = 0; ok && j < n-1; j++ )
            ok = ( a[j] + 1 == a[j+1] );

        for( int j = 0; j < n; j++ )
        {
            if( j%2 == 0 )
                a[j] = (a[j]+1)%n;
            else
                a[j] = (a[j]+n-1)%n;
        }
    }
    if( ok )
        printf("Yes\n");
    else
        printf("No\n");
}
