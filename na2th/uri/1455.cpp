#include<bits/stdc++.h>
#define MP 101
#define eps 1e-9
using namespace std;
typedef double cood;
typedef int num;
typedef int point;
cood x[MP], y[MP], ar, ax, ay;
int n, p[MP];

bool same( point a, point b )
{ return ( fabs(x[a]-x[b]) < eps && fabs(y[a]-y[b]) < eps ); }

bool lexLess( point a, point b )
{
    if( fabs(x[a]-x[b]) < eps ) return y[a] < y[b];
    return x[a] < x[b];
}

inline cood dist( cood xx, cood yy, point a )
{ return sqrt( (xx-x[a])*(xx-x[a]) + (yy-y[a])*(yy-y[a]) ); }

inline cood cP( point a, point b, point c)
{ return (x[a]-x[b])*(y[c]-y[b]) - (x[c]-x[b])*(y[a]-y[b]); }

void findCircle( point a, point b, point c, cood& cx, cood & cy )
{
    cx = 0.5*(x[a]*x[a]+y[a]*y[a]-x[b]*x[b]-y[b]*y[b])*(y[b]-y[c]) -
         0.5*(x[b]*x[b]+y[b]*y[b]-x[c]*x[c]-y[c]*y[c])*(y[a]-y[b]),
    cy = 0.5*(x[b]*x[b]+y[b]*y[b]-x[c]*x[c]-y[c]*y[c])*(x[a]-x[b]) -
         0.5*(x[a]*x[a]+y[a]*y[a]-x[b]*x[b]-y[b]*y[b])*(x[b]-x[c]);
    cx /= (x[a]-x[b])*(y[b]-y[c]) - (x[b]-x[c])*(y[a]-y[b]);
    cy /= (x[a]-x[b])*(y[b]-y[c]) - (x[b]-x[c])*(y[a]-y[b]);
}

void spanCircle2( int k, point p0, point p1, cood& cx, cood& cy, cood& r )
{
    cx = 0.5*(x[p0]+x[p1]);
    cy = 0.5*(y[p0]+y[p1]);
    r  = dist(cx,cy,p0);
    for( int i = 0; i < k; i++ )
        if( dist(cx,cy,p[i]) > r )
        {
            findCircle(p0, p1, p[i], cx, cy);
            r = dist(cx,cy,p[i]);
        }

}

void spanCircle1( int k, point p0, cood& cx, cood& cy, cood& r )
{
    cx = 0.5*(x[p0]+x[p[0]]);
    cy = 0.5*(y[p0]+y[p[0]]);
    r  = dist(cx,cy, p0);
    for( int i = 0; i < k; i++ )
        if( dist(cx,cy,p[i]) > r )
            spanCircle2(i, p0, p[i], cx, cy, r);
}

void spanCircle( int n, cood &cx, cood &cy, cood& r )
{
    // Bem importante, retirar repetidos
    sort(p,p+1, lexLess);
    n = unique(p,p+n) - p;
    random_shuffle(p,p+n);
    if( n > 1 )
    {
        cx = 0.5*(x[p[0]]+x[p[1]]);
        cy = 0.5*(y[p[0]]+y[p[1]]);
        r  = dist(cx,cy,p[1]);
        for( int i = 2; i < n; i++ )
            if( dist(cx,cy,p[i]) > r )
                spanCircle1(i, p[i],cx,cy,r);
    }
    else
    {
        cx = x[0];
        cy = y[0];
        r  = 0.0;
    }
}

int main()
{
    int tc = 1;
    srand( (unsigned) time(0) );
    while( scanf("%d", &n) != EOF && n )
    {
        printf("Instancia %d\n", tc++);
        for( int i = 0; i < n; i++ )
        {
            scanf("%lf %lf", x+i, y+i);
            p[i] = i;
        }
        spanCircle(n,ax,ay,ar);
        printf("%.2lf %.2lf %.2lf\n\n", ax, ay,ar);
    }
}

