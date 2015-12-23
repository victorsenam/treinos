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

const int MN = 2e5+5;
int a[MN], b;
int m, n;

int main()
{
    getnum(n,m);
    for(int i=0;i<n;i++)
        getnum(a[i]);
    sort(a,a+n);
    for(int i=0;i<m;i++)
    {
        getnum(b);
        printf("%d ", upper_bound(a,a+n,b)-a);
    }
    printf("\n");
}
