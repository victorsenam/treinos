#include <cstdio>

using namespace std;

int main()
{
    float a,b,c;
    bool triangle;
    scanf("%f %f %f", &a, &b, &c);
    triangle = c < a + b;
    triangle &= b < a + c;
    triangle &= a < b + c;
    if(triangle)
        printf("Perimetro = %.1f\n", (a+b+c));
    else
        printf("Area = %.1f\n", 0.5*(a+b)*c);
}
