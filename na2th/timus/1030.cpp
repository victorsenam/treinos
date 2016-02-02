#include <bits/stdc++.h>
using namespace std;

typedef double cood;
const cood PI = acos(-1.0);
const cood eps = 1e-9;
enum dim {X,Y,Z};
const vector<int> axis = {X,Y,Z};
typedef cood point[3];
template<typename F> void combine(point c, point a, point b, F f)
{ for(int x: axis) c[x] = f(a[x], b[x]); }
template<typename F> void apply(point a, F f)
{ for(int x: axis) a[x] = f(a[x]); }
inline void add(point c, point b, point a)
{ combine(c, b, a, plus<cood>()); }
inline void sub(point c, point b, point a)
{ combine(c, b, a, minus<cood>()); }
inline cood inner(point a, point b, point c)
{
    cood ans = 0;
    for(int x: axis) ans += (a[x]-c[x])*(b[x]-c[x]);
    return ans;
}
cood (*trig[4])(cood) = {cos, sin, sin, cos};
void build_rotation(cood A[3][3], cood t, dim fix)
{
    int ts = 0;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(i == fix || j == fix) A[i][j] = (i == j);
            else
                A[i][j] = (ts == 1) ? -trig[ts++](t): trig[ts++](t);
}
void apply(cood A[3][3], point c)
{
    point ans;
    for(int i: axis)
    {
        ans[i] = 0;
        for(int j: axis)
            ans[i] += A[i][j]*c[j];
    }
    for(int i: axis) c[i] = ans[i];
}

inline cood read_degree()
{
    cood ans, aux;
    scanf(" %lf%*c", &ans);
    scanf(" %lf%*c", &aux);
    ans += aux/60;
    scanf(" %lf%*c", &aux);
    ans += aux/3600;
    return ans;
}

const cood radius = .5*6875;
inline void build_point(point a)
{
    char aux;
    cood R[3][3];
    cood la = read_degree();
    scanf(" %c%*c %*s", &aux);
    if(aux == 'S') la *= -1;
    la *= PI/180;

    cood lo = read_degree();
    scanf(" %c%*s", &aux);
    if(aux == 'W') lo *= -1;
    lo *= PI/180;

    build_rotation(R, la, Y);
    apply(R, a);
    build_rotation(R, lo, Z);
    apply(R, a);
}

point shp, icb, O;
cood ans;
int main()
{
    while(!feof(stdin))
    {
        for(int x:axis) shp[x] = icb[x] = 0;
        scanf(" %*[^\n] %*[^\n] %*[^\n]");
        if(feof(stdin)) break;
        shp[0] = icb[0] = radius;
        build_point(shp);
        scanf(" %*[^\n]");
        build_point(icb);
        scanf(" %*[^\n]");
        ans = inner(shp, icb, O)/(radius*radius);
        ans = acos(ans)*radius;
        ans = floor(ans*100+.5)/100.0;
        printf("The distance to the iceberg: %.2lf miles.\n", ans);
        if(ans < 100) printf("DANGER!\n");
    }
}
