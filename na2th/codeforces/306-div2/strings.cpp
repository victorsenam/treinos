#include<bits/stdc++.h>
#define MS 100003
using namespace std;
typedef int num;
num apos[MS], aps, bpos[MS], bps, ap, bp, i;
char in;

int main()
{
    while( scanf("%c", &in) && in != '\n' )
    {
        if( in == 'A' )
            apos[aps++] = i;
        else if ( in == 'B' )
            bpos[bps++] = i;
        i++;
    }

    if( aps < 2 || bps < 2 )
        printf("NO\n");
    else
    {
        if( apos[ap] < bpos[bp] )
        {
            bp++;
            while( ap < aps && apos[ap] < bpos[bp] ) ap++;
            if( ap == aps )
                printf("NO\n");
            else
                printf("YES\n");
        }
        else// bpos[bp] < apos[ap]
        {
            ap++;
            while( bp < bps && bpos[bp] < apos[ap] ) bp++;
            if( bp == bps )
                printf("NO\n");
            else
                printf("YES\n");
        }
    }
}
