#include <cstdio>

using namespace std;

int main()
{
    double r;
    scanf("%lf",&r);
    r *= 4*3.14159*r*r;
    r /= 3;
    printf("VOLUME = %.3lf\n", r); 
}
