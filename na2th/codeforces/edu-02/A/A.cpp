#include <bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef int edge;

template<typename T> T& getnum(T& t)
{
    char c; T s=1;
    while(isspace(c=getchar()));
    if(feof(stdin)) exit(0);
    if(c=='-') s=-1,c=getchar();
    t = c-'0';
    while(isdigit(c=getchar())) t = (t<<3)+(t<<1)+c-'0';
    return t*=s;
}
template<typename T,typename... Ts> void getnum(T& t, Ts&... ts)
{ getnum(t); getnum(ts...); }
const int MOD = 1e9+7;
struct mod
{
    num x;
    mod () : x(0) {}
    mod (num a) : x(a) {}
    mod operator+(mod b) { return (1ll*x+1ll*b.x)%MOD; }
    mod operator*(mod b) { return (1ll*x*1ll*b.x)%MOD; }
};

const int MS = 1e5+2;
char in[MS], *p, aux, a[MS], b[MS];
int as, bs, n;

int main()
{
    scanf("%s", in);
    n = strlen(in);
    p = in;
    while( *p != 0 )
    {
        int d = strcspn(p, ",;"), num;
        aux = *(p+d);
    
        num = (0<d);
        for(int i=0; i<d; i++)
            num &= isdigit(p[i]);
        if(p[0] == '0')
            num &= d == 1;
        if(num)
        {
            for(int i=0;i<d;i++)
                a[as++] = p[i];
            a[as++] = ',';
        }
        else
        {
            for(int i=0;i<d;i++)
                b[bs++] = p[i];
            b[bs++] = ',';
        }
        p += max(d+1,1);
    }
    if(as > 0)
    {
        a[as-1] = 0;
        printf("\"%s\"\n", a);
    }
    else printf("-\n");
    if(in[n-1] == ',' || in[n-1] == ';')
        b[bs++] = ',';
    if(bs > 0)
    {
        b[bs-1] = 0;
        b[bs] = 0;
        printf("\"%s\"\n", b);
    }
    else printf("-\n");
}
