#include<cstdio>
double x1,x2,x3,x4,
       y1,y2,y3,y4;
int t;

int main()
{
    scanf("%d", &t);
    for( int tc = 1; tc <= t; tc++ )
    {
        printf("Caso #%d: ", tc);
        scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
        scanf("%lf %lf %lf %lf", &x3, &y3, &x4, &y4);
        double a13 = x1 - x3,
               b13 = y1 - y3,
               c13 = 0.5*(y1*y1-y3*y3) + 0.5*(x1*x1-x3*x3),
               a24 = x2 - x4,
               b24 = y2 - y4,
               c24 = 0.5*(y2*y2-y4*y4) + 0.5*(x2*x2-x4*x4),
               det = a13*b24 - a24*b13;
        printf("%.2lf %.2lf\n", (b24*c13-b13*c24)/det,
                                (a13*c24-a24*c13)/det);
    }
}
