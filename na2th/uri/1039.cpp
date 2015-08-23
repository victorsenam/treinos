#include <cstdio>
#include <cmath>

using namespace std;

int main(int argc, const char *argv[])
{
    int r1, r2, x1,x2, y1,y2;
    float distance;
    while( scanf("%d %d %d %d %d %d", &r1, &x1, &y1, &r2, &x2, &y2) > 0 ){
        distance = 1.0*(x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
        distance = sqrt(distance);
        if( (float)r1 >= (distance + (float)r2 ) )
            printf("RICO\n");
        else
            printf("MORTO\n");
    }
    return 0;
} 
