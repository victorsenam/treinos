#include<bits/stdc++.h>
#define MP 10005 
#define eps 1e-9
typedef double cood;
typedef int point;
cood x[MP], y[MP];
using namespace std;

inline cood cross( point a, point b, point c )
{ return (x[b]-x[a])*(y[c]-y[b])-(y[b]-y[a])*(x[c]-x[b]); }

inline cood inner( point a, point b, point c = MP-1 )
{ return (x[a]-x[c])*(x[b]-x[c]) + (y[a]-y[c])*(y[b]-y[c]); }

bool lexLess( point a, point b )
//{ return ( x[a]==x[b] ) ? y[a]<y[b]: x[a]<x[b] ; }
{ return ( fabs(x[a]-x[b]) < eps ) ? y[a]<y[b]+eps: x[a]<x[b]+eps; }

inline double dist(double ax, double ay, point a)
{ return sqrt( (ax-x[a])*(ax-x[a]) + (ay-y[a])*(ay-y[a]) ); }

int findHull( point * P, int ps, point * H )
{
    if( ps < 3 )
    {
        for( int i = 0; i < ps; i++ ) H[i] = P[i];
        return ps;
    }
    int ans = 0;
    iter_swap( P, min_element(P, P+ps, lexLess) );
    sort(P+1, P+ps, [&](point a, point b)
    { return ( cross(P[0], a, b) == 0 ) ? lexLess(a,b): cross(P[0],a,b) > 0 ; });
    for( int i = 0; i < 3; i++ ) H[ans++] = P[i];
    for( int i = 3; i < ps; i++ )
    {
        while( ans > 1 && cross(H[ans-2], H[ans-1], P[i]) <= 0 ) ans--;
        H[ans++] = P[i];
    }
    return ans;
}

void findCircle( point a, point b, point c , double& ax, double& ay, double& r )
{
    double Aab = x[a]-x[b], Bab = y[a]-y[b], Cab = 0.5*( inner(a,a) - inner(b,b) ),
           Abc = x[b]-x[c], Bbc = y[b]-y[c], Cbc = 0.5*( inner(b,b) - inner(c,c) ),
           det = Aab*Bbc - Bab*Abc; if( fabs(det) < eps ) return;
    ax = (Bbc*Cab - Bab*Cbc)/det; ay = (Aab*Cbc - Abc*Cab)/det;
    r  = dist(ax,ay,a); 
}

// Implementação fica ps*lg(ps) devido as duas ordenaçoes
// para elimitar pontos iguais e pontos colineares
void spanningCircle( point * P, int ps, double& ax, double& ay, double& r )
{
    // Remove pontos iguais, custo (ps)*lg(ps)
    sort(P,P+ps, lexLess);
    ps = unique(P,P+ps,[](point a, point b)
             { return (x[a]==x[b])&&(y[a]==y[b]); }) - P; 
    if( ps == 1 ) { ax = x[0]; ay = y[0]; r = 0.0; return; }
    
    // Resolve pontos colineares calculando o fecho
    // Custo (ps)*lg(ps)
    // point * hull = P; int hs = ps; 
    point * hull = new point [ps];
    int hs = findHull(P, ps, hull);
    random_shuffle(hull, hull+hs);
    ax = 0.5*(x[hull[0]]+x[hull[1]]); ay = 0.5*(y[hull[0]]+y[hull[1]]);
    r  = dist(ax,ay,hull[0]); 
    for( int i = 2; i < hs; i++ )
        if( dist(ax,ay,hull[i]) > r )
        {
            ax = 0.5*(x[hull[0]]+x[hull[i]]); ay = 0.5*(y[hull[0]]+y[hull[i]]);
            r = dist(ax,ay,hull[i]);
            for( int j = 1; j < i; j++ )
                if( dist(ax,ay,hull[j]) > r )
                {
                    ax = 0.5*(x[hull[i]]+x[hull[j]]); ay = 0.5*(y[hull[i]]+y[hull[j]]);
                    r  = dist(ax,ay,hull[i]);
                    for( int k = 0; k < j; k++ )
                        if( dist(ax,ay,hull[k]) > r )
                            findCircle(hull[i],hull[j],hull[k], ax, ay, r);
                }
        }
}

int main()
{
    int n;
    double ans;
    set<point, bool(*)(point,point)> input (lexLess);
    while( scanf("%d", &n) != EOF && n > 0 )
    {
        ans = 1e4 ;
        input.clear();
        for( int i = 0; i < n; i++ )
        {
            scanf("%lf %lf", x+i, y+i);
            auto result = input.insert(i);
            auto lb = result.first,
                 ub = result.first;
            double local = 1e9;
            if( lb != input.begin() ) --lb;
            while( fabs(x[*lb]-x[i]) < ans && lb != input.begin() )
            {
                local = min(local, sqrt(inner(i,i,*lb))) ; 
                --lb;
            } 
            if( lb != result.first )
                local  = min(local, sqrt( inner(i,i,*lb) ));

            if( ub != input.end() ) ++ub;
            while( fabs(x[*ub]-x[i]) < ans && ub != input.end() )
            {
                local = min( local, sqrt(inner(i,i,*ub)));
                ++ub;
            }
            ans = min(ans, local);
        }
        if( ans + eps > 1e4 )
            printf("INFINITY\n");
        else
            printf("%.4lf\n", ans);
    }
}
