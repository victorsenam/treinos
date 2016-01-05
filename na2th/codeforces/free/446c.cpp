#include <bits/stdc++.h>
using namespace std;
typedef long long num;
const int N = 3e5;
const num MOD = 1e9+9;

struct mod
{
    int x;
    mod(): x(0) {}
    mod(int a) { x = a%MOD; }
    mod operator+(const mod& b){ return (num(x)+num(b.x))%MOD; }
    mod operator-(const mod& b){ return (MOD + x - b.x)%MOD;   } 
    mod operator*(const mod& b){ return (num(x)*num(b.x))%MOD; }
};

mod base[2][2], fib[N+5][2][2];
void multBy(mod a[2][2], mod b[2][2])
{
    mod ans[2][2];
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
        {
            ans[i][j] = 0;
            for(int k=0;k<2;k++)
                ans[i][j] = ans[i][j] + a[i][k]*b[k][j];
        }
    for(int i=0;i<4;i++)
        a[i/2][i%2] = ans[i/2][i%2];
}
void q_fib(mod f1, mod f2, mod& f3, mod& f4, int d)
{
    f4 = f2*fib[d][0][0] + f1*fib[d][0][1];
    f3 = f2*fib[d][1][0] + f1*fib[d][1][1];
}

int n;
mod tree[2*N], f1[N], f2[N];
int k[2*N];
inline void apply(int p, mod f1, mod f2)
{
    mod f3, f4;
    q_fib(f1,f2,f3,f4,k[p]);
    tree[p] = tree[p] + f4 - f2;
    if(p < n)
        ::f1[p] = ::f1[p] + f1, ::f2[p] = ::f2[p] + f2;
}
void unlazy(int p)
{
    if(!p) return;
    unlazy(p>>1);
    if(p < n)
    {
        mod f3, f4;
        q_fib(f1[p],f2[p],f3,f4,k[p<<1]);
        apply(p<<1  , f1[p], f2[p]);
        apply(p<<1|1, f3, f4);
        f1[p] = f2[p] = 0;
    }
}
void update(int p)
{
    if(!p) return;
    if(p < n)
    {
        mod f3, f4; q_fib(f1[p],f2[p],f3,f4,k[p]);
        tree[p] = tree[p<<1] + tree[p<<1|1] + f4 - f2[p];
    }
    update(p>>1);
}
void add(int l, int r, mod f1, mod f2, int s)
{
    if(l >= r) return;
    mod f3, f4;
    if(l&1)
    {
        apply(l, f1, f2);
        q_fib(f1,f2,f3,f4,k[l]);
        f1 = f3; f2 = f4;
        s -= k[l];
        l++;
    }
    if(r&1)
    {
        --r;
        q_fib(f1,f2,f3,f4,s-k[r]);
        apply(r, f3, f4);
        s -= k[r];
    }
    add(l>>1, r>>1, f1, f2, s);
}
mod query(int l, int r)
{
    mod ans = 0;
    if(l >= r) return ans;
    if(l&1) ans = ans + tree[l++];
    if(r&1) ans = ans + tree[--r];
    return ans + query(l>>1,r>>1);
}

int q;
int main()
{
    base[0][0] = base[0][1] = base[1][0] = 1;
    fib[0][0][0] = fib[0][1][1] = 1;
    for(int i=0;i<4;i++) fib[1][i/2][i%2] = base[i/2][i%2];
    for(int i=2;i<N+5;i++)
    {
        for(int k=0;k<4;k++)
            fib[i][k/2][k%2] = fib[i-1][k/2][k%2];
        multBy(fib[i], base);
    }
    scanf(" %d%d", &n, &q);
    for(int i=0;i<n;i++)
    {
        int in;
        scanf(" %d", &in);
        tree[i+n] = in;
        k[i+n] = 1;
    }
    for(int i=n-1;i>0;--i)
        tree[i] = tree[i<<1] + tree[i<<1|1],
        k[i] = k[i<<1] + k[i<<1|1];
    while(q--)
    {
        int cmd, lo, hi;
        scanf(" %d%d%d", &cmd, &lo, &hi); --lo;
        if(cmd == 2)
        {
            unlazy(lo+n);
            unlazy(hi+n-1);
            printf("%d\n", query(lo+n,hi+n).x);
        }
        else
        {
            add(lo+n, hi+n, 1, 1, hi-lo);
            update(lo+n);
            update(hi+n-1);
        }
    }
}
