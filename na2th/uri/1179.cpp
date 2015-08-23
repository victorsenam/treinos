#include <cstdio>

using namespace std;

int main()
{
    int par[5], impar[5], ps = 0, is = 0, i, num,j;
    for (i = 0; i < 15; i++) {
        scanf("%d", &num);
        if( num%2 == 0 )
        {
            if(ps == 5){
                for (j = 0; j < 5; j++) 
                    printf("par[%d] = %d\n", j, par[j]);
                ps = 0;
            }
            par[ps++] = num;
        }
        else
        {
            if( is == 5 ){
                for (j = 0; j < 5; j++) 
                    printf("impar[%d] = %d\n", j, impar[j]);
                is = 0;
            }
            impar[is++] = num;
        }
    }
    for (i = 0; is > 0 ; i++, is--)
        printf("impar[%d] = %d\n", i, impar[i]);

    for (i = 0; ps > 0 ; i++, ps--)
        printf("par[%d] = %d\n", i, par[i]);
}
