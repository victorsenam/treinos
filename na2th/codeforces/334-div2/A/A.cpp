#include <bits/stdc++.h>
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;

double m[5], w[5], x[5] = {500, 1000, 1500, 2000, 2500};
double ans;
int h;

int main()
{
    for(int i=0;i<5;i++)
        scanf(" %lf",  m+i);
    for(int i=0;i<5;i++)
        scanf(" %lf", w+i);
    ans = double(0);
    for(int i=0;i<5;i++)
        ans += max(.3*x[i], (1-m[i]/250)*x[i] - 50*w[i]);
    scanf(" %d", &h);
    ans += 100*h;
    scanf(" %d", &h);
    ans -= 50*h;
    printf("%.0lf\n", ans);
}
