#include <cstdio>

using namespace std;

int main()
{
    int time, speed;
    float ans;
    scanf("%d %d", &time, &speed);
    ans = (float) time*speed/12;
    printf("%.3f\n", ans);
}
