#include <cstdio>
#include <cmath>

using namespace std;

int main()
{
    int x,y, dx,dy;
    float ans;
    dx = dy = 0;
    scanf("%d %d", &x, &y);
    dx += x; dy += y;
    scanf("%d %d", &x, &y);
    dx -= x; dy -= y;
    ans = dx*dx + dy*dy;
    ans = sqrt(ans);
    printf("%.4f\n", ans);
}
