#include <cstdio>

using namespace std;

int main()
{
    double a,b,c, ans;
    scanf("%lf %lf %lf", &a, &b, &c);

    ans = a*c/2;
    printf("TRIANGULO:%.3f\n",ans);
    ans = c*c*3.14159;
    printf("CIRCULO:%.3f\n",ans);
    ans = (a+b)*c/2;
    printf("TRAPEZIO:%.3f\n",ans);
    ans = b*b;
    printf("QUADRADO:%.3f\n",ans);
    ans = a*b;
    printf("RETANGULO:%.3f\n",ans);
}
