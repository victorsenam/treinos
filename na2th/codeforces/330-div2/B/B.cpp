#include <bits/stdc++.h>
using namespace std;
typedef long long num;
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
mod ans;
num n, k, fst, big, a[MN], b[MN], powers[10];
num lo, hi, mid, c, d;

int main()
{
    powers[0] = 1ll;
    for(int i=1;i<10;i++)
        powers[i] = 10ll*powers[i-1];
    getnum(n,k);
    ans = 1;
    for(int i=0;i<n/k;i++) getnum(a[i]);
    for(int i=0;i<n/k;i++) getnum(b[i]);
    for(int i=0;i<n/k;i++)
    {
        big = (powers[k]%a[i]==0) ? powers[k]-a[i]: powers[k]-powers[k]%a[i];
        hi = big/a[i]+1;
        lo = 0;
        while(lo < hi)
        {
            mid = lo + (hi-lo)/2;
            fst = mid*a[i];
            for(int j=0;j<k-1;j++) fst /= 10;
            if(fst>=b[i]) hi = mid;
            else lo = mid + 1;
        }
        c = lo;
        hi = big/a[i]+1;
        lo = 0;
        while(lo < hi)
        {
            mid = lo + (hi-lo)/2;
            fst = mid*a[i];
            for(int j=0;j<k-1;j++) fst /= 10;
            if(fst>b[i]) hi = mid;
            else lo = mid + 1;
        }
        d = lo;
        ans = mod(1+big/a[i]-(d-c))*ans;
    }
    printf("%I64d\n", ans.x);
}
