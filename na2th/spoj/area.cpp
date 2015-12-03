#include <bits/stdc++.h>
#define MAX 10000

using namespace std;

typedef int cood;
typedef pair<cood, cood> point;

int N, area, ps;
point p[MAX];

cood cP(point a, point b, point c)
{
    // a.f a.s 1
    // b.f b.s 1
    // c.f c.s 1
    return (
            a.first*(b.second - c.second) +
            a.second*(c.first - b.first) +
            b.first*c.second - b.second*c.first
            );
}

int main()
{
    scanf("%d", &N);
    ps = 0;
    for(int i = 0; i < N; i++)
    {
        cood x, y;
        scanf("%d %d", &x, &y);
        p[ps++] = make_pair( x,y );
    }

    area = 0;

    for(int i = 1; i < N; i++)
        area += cP( p[0], p[i], p[(i+1)%N] );
    printf("%d\n", area/2);
}
