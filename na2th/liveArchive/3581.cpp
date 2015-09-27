#include<bits/stdc++.h>
#define MP  4005
#define eps 1e-9
typedef int cood;
typedef int point;
cood x[MP], y[MP];
using namespace std;

inline cood cross( point a, point b, point c )
{ return (x[b]-x[a])*(y[c]-y[b])-(y[b]-y[a])*(x[c]-x[b]); }

inline cood inner( point a, point b, point c = MP-1 )
{ return (x[a]-x[c])*(x[b]-x[c]) + (y[a]-y[c])*(y[b]-y[c]); }

bool lexLess( point a, point b )
{ return ( x[a]==x[b] ) ? y[a]<y[b]: x[a]<x[b] ; }
// { return ( fabs(x[a]-x[b]) < eps ) ? y[a]<y[b] : x[a]<x[b] ; }

inline bool between( point a, point b, point c )
{ return ( cross(a,b,c) == 0 ) && ( inner(a,b,c) <= 0 ) ; }

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

bool inConvex( point * P, int ps, point q )
{
    int lo = 1,
        hi = ps-1;
    if( ps < 3 ) return between(P[0], P[1], q);
    while( lo + 1 < hi )
    {
        int mid = (lo+hi)/2,
            val = cross(P[0], P[mid], q);
        if( val == 0 ) return inner(P[0],P[mid],q) <= 0 ; 
        if( val > 0 )  lo = mid;
        else           hi = mid;
    }
    return ( cross(P[0] ,P[lo],q) >= 0 ) && 
           ( cross(P[lo],P[hi],q) >= 0 ) &&
           ( cross(P[hi],P[0] ,q) >= 0 ) ;
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
    int ds, ps, cnt, tc = 1;
    point D[2001], P[2001], hD[2001], hP[2001];
    cood ix0, iy0, ix1, iy1;
    while( scanf("%d %d", &ds, &ps) != EOF && ds && ps )
    {
        cnt = 0;
        if( tc > 1 ) printf("\n");
        printf("Case %d: ", tc++);
        for( int i = 0; i < ds; i++ )
        {
            scanf("%d %d %d %d", &ix0, &iy0, &ix1, &iy1);
            x[cnt] = ix0; y[cnt] = iy0; D[4*i+0] = cnt++;
            x[cnt] = ix0; y[cnt] = iy1; D[4*i+1] = cnt++;
            x[cnt] = ix1; y[cnt] = iy0; D[4*i+2] = cnt++;
            x[cnt] = ix1; y[cnt] = iy1; D[4*i+3] = cnt++;
        }
        for( int i = 0; i < ps; i++ )
        {
            scanf("%d %d %d %d", &ix0, &iy0, &ix1, &iy1);
            x[cnt] = ix0; y[cnt] = iy0; P[4*i+0] = cnt++;
            x[cnt] = ix0; y[cnt] = iy1; P[4*i+1] = cnt++;
            x[cnt] = ix1; y[cnt] = iy0; P[4*i+2] = cnt++;
            x[cnt] = ix1; y[cnt] = iy1; P[4*i+3] = cnt++;
        }
        int hDs = findHull(D, 4*ds, hD),
            hPs = findHull(P, 4*ps, hP);
        bool ok = true;
        for( int i = 0; ok && i < hPs; i++ )
            ok = !inConvex(hD, hDs, hP[i]);
        for( int i = 0; ok && i < hDs; i++ )
            ok = !inConvex(hP, hPs, hD[i]);

        if( ok )
            printf("It is possible to separate the two groups of vendors.\n");
        else
            printf("It is not possible to separate the two groups of vendors.\n");
    }
}
