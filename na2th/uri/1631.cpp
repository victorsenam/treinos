#include<bits/stdc++.h>
#define MP 101
#define eps 1e-9
using namespace std;
typedef int cood;
typedef int point;

cood x[MP], y[MP];
point p[MP];
int n;
double ans;

bool lexLess(point a, point b)
{
    if( x[a] == x[b] ) return y[a] < y[b];
    return x[a] < x[b];
}

bool same( point a, point b)
{ return (x[a]==x[b]) && (y[a]==y[b]); }

inline cood cP( point a, point b, point c )
{ return (x[a]-x[b])*(y[c]-y[b])-(x[c]-x[b])*(y[a]-y[b]); }

inline double dist( point a, point b, point c )
{ return 1.0*cP(a,b,c)/sqrt( (x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]) ); }

int main()
{
    while( scanf("%d", &n) > 0 && n > 0 )
    {
        for( int i = 0; i < n; i++ )
        {
            scanf("%d %d", x+i, y+i);
            p[i] = i;
        }
        sort(p, p+n, lexLess);
        n = unique(p, p+n, same) - p;

        if( n > 2 )
        {
            ans = DBL_MAX;
            for( int i = 0; i < n; i++ )
                for( int j =i+1; j < n; j++ )
                {
                    double lp = 0.0, ln = 0.0;
                    for( int k = 0; k < n; k++ )
                    {
                        lp += max( dist(p[i],p[j],p[k]), 0.0 );
                        ln += max( -dist(p[i],p[j],p[k]), 0.0 );
                    }
                    ans = min(ans, fabs(lp-ln));
                }
        }
        else
            ans = 0.0;
        printf("%.3lf\n", ans);
    }
}
