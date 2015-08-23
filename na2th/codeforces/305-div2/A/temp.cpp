#include <bits/stdc++.h>
using namespace std;
typedef int num;
const int MS = 1003;
char in[MS], pil[MS];
num k, ps, is, i, j;

int main()
{
    scanf("%s", in);
    scanf("%d", &k);
    is = strlen(in);

    if( is%k != 0 || is < k )
        printf("NO\n");
    else
    {
        bool ok = true;
        for( i = 0; ok && i < is; i += is/k )
        {
            ps = 0;
            for( j = 0; j < is/(2*k); j++ )
                pil[ps++] = in[i+j];

            if( (is/k)&1 ) j++;

            for( ; ok && j < is/k; j++ )
                ok = ( in[i+j] == pil[--ps] );
        }
        if( ok )
            printf("YES\n");
        else
            printf("NO\n");
    }
}
