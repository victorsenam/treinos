#include <bits/stdc++.h>
#define PI (acos(-1.0))
#define MAX 100000

using namespace std;

typedef int cood;
typedef pair<cood, cood> point;

point P[MAX];
int hull[MAX], hs, ps, a, d;

cood cP(point a, point b, point c)
{
    return ( 
            a.first*(b.second - c.second) +
            a.second*(c.first - b.first) +
            b.first*c.second - b.second*c.first
           );
}

bool grahamLess(point a, point b)
{
    cood val = cP( *P, a, b );
    if( !val )
        return (a.first) < (b.first);
    return val > 0;
}

void grahamScan()
{
    // Acha o ponto mais a esquerda
    int min = 0, i;
    for(i = 1; i < ps; i++)
        if( P[i] < P[min] )
            min = i;
    swap( P[0], P[min] );
    // Ordena pontos por angulo
    sort( P+1, P+ps, grahamLess);

    // Calcula o hull
    hs = 0;
    for( i = 0; i < 3; i++ )
        hull[hs++] = i;

    for( i = 3 ; i < ps; i++ )
    {
        while( hs > 1 && cP( P[hull[hs-2]], P[hull[hs-1]], P[i]) <= 0 )
            hs--;
        hull[hs++] = i;
    }
}

double dist(point a, point b)
{
    double norm = 0;
    norm += (a.first - b.first)*(a.first - b.first);
    norm += (a.second - b.second)*(a.second - b.second);
    return sqrt(norm);
}

int main()
{
    while( scanf("%d %d", &a, &d) > 0 )
    {
        ps = 0;
        cood x,y;
        for(int i = 0; i < a; i++)
        {
            scanf("%d %d", &x, &y);
            P[ps++] = make_pair( x, y);
        }
        grahamScan();
        double ans = 0;
        for( int i = 0; i < hs; i++ )
            ans += dist(P[hull[i]], P[hull[(i+1)%hs]]);
        printf("%.2f\n", ans);
    }
}
