#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef int cood;
typedef int point;
const int    MP  = 1002;
const double PI  = (acos(-1.0));
const double eps = (1e-9);
cood x[MP], y[MP];
point anchor, in[MP], hull[MP];
num n, l;

inline cood cross( point a, point b, point c )
{ return (x[b]-x[a])*(y[c]-y[b])-(y[b]-y[a])*(x[c]-x[b]); }
inline cood inner( point a, point b, point c = MP-1 )
{ return (x[a]-x[c])*(x[b]-x[c]) + (y[a]-y[c])*(y[b]-y[c]); }
inline double dist(point b, point a)
{ return sqrt( inner(b,b,a) ); }
bool lexLess( point a, point b )
{ return ( x[a]==x[b] ) ? y[a]<y[b]: x[a]<x[b] ; }
bool grahamLess( point a, point b )
{
    num val = cross(anchor, a, b);
    if( val == 0 ) return lexLess(a,b);
    return val > 0;
}
int findHull( point * P, int ps, point * H )
{
    int hs=0;
    iter_swap(P, min_element(P,P+ps,lexLess));
    anchor = P[0]; sort(P+1,P+ps,grahamLess);
    for(int i=0;i<ps;i++)
    {
        while( hs > 1 && cross(H[hs-2],H[hs-1],P[i]) <= 0 )
            hs--;
        H[hs++] = P[i];
    }
    return hs;
}

int main()
{
    int tc;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d %d", &n, &l);
        for(int i=0;i<n;i++)
        {
            scanf("%d %d",x+i, y+i);
            in[i] = i;
        }
        int hs = findHull(in, n, hull);
        double ans = 2*PI*l;
        for(int i=0;i<hs;i++)
            ans += dist(hull[i],hull[(i+1)%hs]);
        printf("%.0f\n", ans);
        if(tc>0) printf("\n");
    }
}
