#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
    int n, primos[2000000], ps = 0;
    primos[ps++] = 2;
    while( scanf("%d", &n) != EOF )
    {
        if(primos[ps-1] < n )
        {
            for(int i = primos[ps-1] + 1 ; i < n ; i++)
            {
                int primo = 1;
                for(int pp = 0 ; primo && primos[pp]*primos[pp] <= i && pp < ps ; pp++ )
                    if( i%primos[pp] == 0 )
                        primo = 0;

                if(primo)
                    primos[ps++] = i;

            }
        }
        int hp = upper_bound(primos, primos+ps, n) - primos;
        for(int i = 0; i < ps && primos[i]*primos[i] <= n ; i++)
            for(int j = 1; j < ps && pow(primos[i], primos[j] - 1) <= n; j++)
                hp++;


        printf("%d\n", hp);
    }
}
