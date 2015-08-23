#include <cstdio>

using namespace std;

int main()
{
    double a, b, c, mean;
    scanf("%lf %lf %lf", &a, &b, &c);
    mean = (2.0*a) + (3.0*b) + (5.0*c);
    mean /= 10;
    printf("MEDIA = %.1lf\n", mean);
}
