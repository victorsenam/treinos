#include <bits/stdc++.h>
#define mp make_pair
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

const int MN = 1e5+7;
int n;
int in[MN], fin[MN], lo[MN], hi[MN], p[MN], cmp[MN], cs, is;

bool inRange(int l, int x, int h)
{ return l <= x && x < h; }
bool lexLess(int i, int j)
{ return mp(lo[i], -hi[i]) < mp(lo[j], -hi[j]); }

int main()
{
    getnum(n);
    for(int i=0;i<n;i++)
    {
        scanf(" %d", in+i);
        fin[i] = in[i];
    }
    is = 0;
    sort(fin, fin+n);
    for(int i=0;i<n;i++)
    {
        int ll = lower_bound(fin, fin+n, in[i]) - fin,
            hh = upper_bound(fin, fin+n, in[i]) - fin - 1;
        if( inRange(ll, i, hh+1) ) continue;
        if ( i < ll )
        {
            lo[is] = i; hi[is] = ll; p[is] = is; is++;
        }
        else // hh < i
        {
            lo[is] = hh; hi[is] = i; p[is] = is; is++;
        }
    }
    if( is == 0 )
    {
        printf("%d\n", n);
        return 0;
    }

    sort(p, p+is, lexLess);
    cs++;
    for(int i=0; i<is; i++)
    {
        if( cmp[p[i]] ) continue;
        int reach = hi[p[i]];
        int j = i;
        while ( j < is && lo[p[j]] <= reach )
            reach = max(reach, lo[p[j++]]);
        for(int k=lo[i]; k<=reach; k++)
            cmp[k] = cs;
        cs++;
    }

    printf("%d\n", cs-1);
}
