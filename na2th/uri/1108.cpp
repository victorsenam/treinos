#include<bits/stdc++.h>
using namespace std;
using cood  = double;
using point = complex<cood>;
const cood tau = 2*acos(-1.0);
const cood eps  = 1e-9;
const cood eps2 = 2*eps + eps*eps;

inline cood x(const point& a)
{ return real(a); }
inline cood y(const point& a)
{ return imag(a); }
inline cood inner(const point& a,const point& b)
{ return x(a)*x(b) + y(a)*y(b); }
inline cood cross(const point& a,const point& b)
{ return x(a)*y(b) - y(a)*x(b); }
inline cood area(const point& a,const point& b,const point& c)
{ return cross(b-a, c-a); }
inline point rotate(const point& a,const cood& t)
{ return a*polar(1.0,t); }
// Projeta o ponto c na linha ab
inline point projPointLine(const point& a,const point& b,const point& c)
{ return a + (b-a)*inner(c-a,b-a)/norm(b-a); }
// Projeta o ponto c no segmento ab
point projPointSeg(const point& a,const point& b,const point& c)
{
    if( norm(b-a) < eps ) return a;
    cood t = inner(c-a,b-a)/norm(b-a);
    if( t < 0 ) return a;
    if( t > 1 ) return b;
    return a + t*(b-a);
}
// Retorna distância entre ponto c e linha ab
inline cood distLinePoint(const point& a,const point& b,const point& c)
{ return cross(c-a,b-a)/norm(b-a); }
// Retorna distância entre ponto c e segmento ab
inline cood distSegPoint(const point& a,const point& b,const point& c) 
{ return sqrt(norm(c-projPointSeg(a,b,c))); }
// Retorna se ponto c entre a e b
inline bool between(const point& a,const point& b,const point& c)
{ return fabs(cross(a-c,b-c)) < eps && inner(a-c,b-c) < eps; }
// Testa se retas paralelas
inline bool parallelLines(const point& a,const point& b,const point& c,const point& d)
{ return fabs(cross(b-a,d-c)) < eps; }
// Retorna a intersecção entra ab e cd
// Amo álgebras de lie :D
point intersect(const point& a,const point& b,const point& c,const point& d)
{ return (a + (b-a)*(cross(c-a,d-c)/cross(b-a,d-c))); }
point circumcenter(const point& a,const point& b,const point& c)
{
    point ab = 0.5*(a+b) + rotate(b-a,0.25*tau),
          bc = 0.5*(b+c) + rotate(c-b,0.25*tau);
    return intersect(0.5*(a+b), ab, 0.5*(b+c), bc);
}
point spanningCircle( point * P, int ps, cood& r )
{
    if( ps < 2 )
    {
        r = 0.0; 
        return *P;
    }
    random_shuffle(P,P+ps);
    point ans = 0.5*(P[0]+P[1]); r = sqrt(norm(P[0]-ans));
    for( int i = 2; i < ps; i++ ) if( norm(ans-P[i]) > r*r )
    {
        ans = 0.5*(P[0]+P[i]); r = sqrt(norm(P[0]-ans));
        for( int j = 1; j < i; j++ )  if( norm(ans-P[j]) > r*r )
        {
            ans = 0.5*(P[i]+P[j]); r = sqrt(norm(P[i]-ans));
            for( int k = 0; k < j; k++ ) if( norm(ans-P[k]) > r*r )
            {
                ans = circumcenter(P[i],P[j],P[k]);
                r   = sqrt(norm(P[i]-ans));
            }
        }
    }
    return ans;
}

int main()
{
    srand( (unsigned) time(0) );
    int n; cood ix, iy, inAns, outAns, ans;
    point in[42], curr, inCirc, outCirc;
    unsigned long long covered;
    while( scanf("%d", &n) != EOF && n )
    {
        for( int i = 0; i < n; i++ )
        {
            scanf("%lf %lf", &ix, &iy);
            in[i] = point (ix, iy);
        }
        ans = DBL_MAX;
        random_shuffle(in, in+n);
        for( int i = -1; i < n; i++ )
            for( int j = i+1; j < n; j++ )
                for( int k = j+1; k < n; k++ )
                {
                    if( i < 0 )
                        inCirc = 0.5*(in[j]+in[k]);
                    else
                        inCirc = circumcenter(in[i],in[j],in[k]);

                    inAns   = sqrt(norm(in[j]-inCirc));
                    covered = 0ull;
                    for( int ii = 0; ii < n; ii++ )
                        if( norm(inCirc-in[ii]) < inAns*inAns + 2*eps*inAns + eps*eps )
                            covered |= (1ull<<ii);

                    // Monta circulo complementar
                    int p = 0, f, s;
                    while( p < n && (covered&(1ull<<p)) ) p++;
                    f = p++;
                    while( p < n && (covered&(1ull<<p)) ) p++;
                    s = p;

                    if( s < n )
                    {
                        outCirc = 0.5*(in[f]+in[s]);
                        outAns  = sqrt(norm(outCirc-in[p]));
                        for( int ii = f; ii < n; ii++ )
                            if( norm(outCirc-in[ii]) + eps > outAns*outAns && !(covered&(1ull<<ii)) )
                            {
                                outCirc = 0.5*(in[f]+in[ii]); outAns = sqrt(norm(in[ii]-outCirc));
                                for( int jj = f+1; jj < ii; jj++ )
                                    if( norm(outCirc-in[jj]) + eps > outAns*outAns && !(covered&(1ull<<jj)) )
                                    {
                                        outCirc = 0.5*(in[ii]+in[jj]); outAns = sqrt(norm(in[ii]-outCirc));
                                        for( int kk = 0; kk < jj; kk++ )
                                            if( norm(outCirc-in[kk]) + eps > outAns*outAns && !(covered&(1ull<<kk)) )
                                            {
                                                outCirc = circumcenter(in[ii],in[jj],in[kk]);
                                                outAns  = sqrt(norm(in[ii]-outCirc));
                                            }
                                    }
                            }
                        ans = min(ans, max(inAns, outAns));
                    }
                    else
                        ans = min(ans, inAns);
                }
        printf("%.2lf\n", ans);
    }
}
