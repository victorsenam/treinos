#include <cstdio>

using namespace std;

int main()
{
    int km;
    float liters, ans;

    scanf("%d %f", &km, &liters);
    ans = (float)km/liters;
    printf("%.3f km/l\n", ans);
}
