#include <cstdio>

using namespace std;

int main()
{
    double a, b, mean;
    scanf("%lf %lf", &a, &b);
    mean = (3.5*a) + (7.5*b);
    mean /= 11;
    printf("MEDIA = %.5lf\n", mean);
}
