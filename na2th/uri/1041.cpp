#include <cstdio>

using namespace std;

int main()
{
    float x,y;
    scanf("%f %f", &x, &y);
    if( x != 0 && y != 0 )
    {
        printf("Q");
        if( x > 0 && y > 0 )
            printf("1\n");        
        else if( x < 0 && y > 0 )
            printf("2\n");
        else if( x < 0 && y < 0 )
            printf("3\n");
        else
            printf("4\n");
    }
    else
    {
        if( x == 0 && y != 0 )
            printf("Eixo Y\n");
        else if ( y == 0 && x != 0)
            printf("Eixo X\n");
        else
            printf("Origem\n");
    }
}
