#include <bits/stdc++.h>
using namespace std;
typedef long long num;
const int N = 1e5+1;

int out[20], os;
template<typename T> void getnum(T & t)
{
    char c; t = 0;
    while(isspace(c=getchar_unlocked()));
    t = c-48;
    while(isdigit(c=getchar_unlocked()))
        t = (t<<3) + (t<<1) + c - 48;
}

int n;
num a[N], c[N];

void update(num *v, int p, num x)
{ for(;p>0;p-=(p&-p)) v[p] += x; }
inline void update(num * v, int l, int r, num x)
{ update(v, r, x); update(v, l-1, -x); }
void update(int l, int r, num x)
{
    update(c, l,   r, -num(l-1)*x);
    update(c, r+1, n, num(r-l+1)*x);
    update(a, l, r, x);
}

num get(num *v, int p)
{
    num ans = 0;
    for(;p && p<=n;p+=(p&-p)) ans += v[p];
    return ans;
}
num get(int p)
{ return get(c, p) + num(p)*get(a,p); }
num query(int l, int r)
{ return get(r) - get(l-1); }

int t, q;
int main()
{
    getnum(t);
    while(t--)
    {
        int cmd, l, r;
        num v;
        getnum(n); getnum(q);
        for(int i=0;i<n+1;i++) a[i] = c[i] = 0;
        while(q--)
        {
            getnum(cmd); getnum(l); getnum(r);
            if(cmd == 1) printf("%lld\n", query(l, r));
            else getnum(v), update(l,r,v);
        }
    }
}
