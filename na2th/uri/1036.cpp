#include <cstdio>
#include <cmath>

using namespace std;

int main(){
    double a, b,c,delta,x1,x2;
    scanf("%lf %lf %lf",&a, &b, &c);
    delta = b*b-4*a*c;
    if(delta < 0){
        printf("Impossivel calcular\n");
        return 0;
    }
    else{
        x1 = (-1*b + sqrt(delta))/(2*a);
        x2 = (-1*b - sqrt(delta))/(2*a);
        printf("R1 = %.5lf\nR2 = %.5lf\n", x1, x2);
    }
}
