#include<bits/stdc++.h>
using namespace std;
typedef int num;
char in[102];
num ins, i, j, k, sol;
bool good;

int main()
{
    scanf("%s", in);
    while( in[ins] != '\0' )
    {
        if( (in[ins]-0x30)%8 == 0 )
        {
            printf("YES\n");
            printf("%c\n", in[ins]);
            return 0;
        }
        ins++;
    }

    good = false;
    for( i = 0; !good && i < ins; i++ )
        for( j = i+1; !good && j < ins; j++ )
        {
            sol = (in[i]-0x30)*10 + (in[j]-0x30);
            good = ( sol%8 == 0 );
        }
    for( i = 0; !good &&  i < ins; i++ )
        for( j = i+1; !good && j < ins; j++ )
            for( k = j+1; !good &&  k < ins; k++ )
            {
                sol = (in[i]-0x30)*100 + (in[j]-0x30)*10 + (in[k]-0x30);
                good = ( sol%8 == 0 );
            }

    if( good )
    {
        printf("YES\n");
        printf("%d\n", sol);
    }
    else
        printf("NO\n");
}
