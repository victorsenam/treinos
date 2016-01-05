#include <bits/stdc++.h>
using namespace std;
typedef long long num;
const int N = 1e5;
const num MOD = 1e9+7;

struct mod
{
    int x;
    mod() : x(0) {}
    mod(int _x) : x(_x%MOD) {}
    mod operator+(const mod& b) { return (num(x)+num(b.x))%MOD;}
    mod operator*(const mod& b) { return (num(x)*num(b.x))%MOD;}
    mod operator-(const mod& b) { return (num(x)+MOD-num(b.x))%MOD;}
};

int n;
mod tree[2*N], sz[2*N], a[N], m[N];
bool c[N];
inline void add(int p, mod x)
{
    tree[p] = tree[p] + sz[p]*x;
    if(p < n) a[p] = a[p] + x;
}
inline void mul(int p, mod x)
{
    tree[p] = tree[p]*x;
    if(p < n) a[p] = a[p]*x, m[p] = m[p]*x;
}
inline void frc(int p, mod x)
{
    tree[p] = sz[p]*x;
    if(p < n) a[p] = x, c[p] = 1;
}
void apply(int l, int r, void(*modify)(int, mod), num x)
{
    if(l >= r) return;
    if(l&1) modify(l++, x);
    if(r&1) modify(--r, x);
    apply(l>>1,r>>1, modify, x);
}
mod query(int l, int r)
{
    mod ans = 0;
    if(l >= r) return ans;
    if(l&1) ans = ans + tree[l++];
    if(r&1) ans = ans + tree[--r];
    return ans + query(l>>1,r>>1);
}
void unlazy(int p)
{
    if(!p) return;
    unlazy(p>>1);
    if(p < n)
    {
        if(c[p])
            frc(p<<1, a[p]), frc(p<<1|1, a[p]);
        else
        {
            if(m[p].x != 1) mul(p<<1, m[p]), mul(p<<1|1, m[p]);
            if(a[p].x != 0) add(p<<1, a[p]), add(p<<1|1, a[p]);
        }
        a[p] = c[p] = 0; m[p] = 1;
    }
}
void update(int p)
{
    if(!p) return;
    if(p < n)
    {
        if(c[p])
            tree[p] = sz[p]*a[p];
        else
            tree[p] = (tree[p<<1] + tree[p<<1|1])*m[p] + a[p]*sz[p];
    }
    update(p>>1);
}

int q;
int main()
{
    scanf(" %d%d", &n, &q);
    for(int i=0;i<n;i++)
        scanf(" %d", tree+i+n), sz[i+n] = 1;
    for(int i=n-1;i>0;--i)
        tree[i] = tree[i<<1] + tree[i<<1|1],
        sz[i] = sz[i<<1] + sz[i<<1|1],
        a[i] = c[i] = 0, m[i] = 1;
    while(q--)
    {
        int cmd, l, r;
        scanf(" %d%d%d", &cmd, &l, &r); --l;
        unlazy(l+n); unlazy(r+n-1);
        if(cmd == 4)
            printf("%d\n", query(l+n, r+n));
        else
        {
            int x; scanf(" %d", &x);
            if(cmd == 1) apply(l+n, r+n, add, x);
            if(cmd == 2) apply(l+n, r+n, mul, x);
            if(cmd == 3) apply(l+n, r+n, frc, x);
            update(l+n); update(r+n-1);
        }
    }
}
