#include<bits/stdc++.h>
using namespace std;
typedef long long num;
const int MT = 100002;
num tree[2*MT], lazy[MT], k[2*MT];
int n,h,c,t;

inline void build()
{
    for(int i=n;i<2*n;i++)
        k[i] = 1ll;
    h = 0;
    for(int aux=n;aux>0;aux>>=1) h++; 
    for(int i=n-1;i>0;i--)
    {
        tree[i] = tree[i<<1] + tree[i<<1^1];
        k[i]    =    k[i<<1] +    k[i<<1^1];
    }
}

inline void apply(int p, num val)
{
    tree[p] += val*k[p];
    if( p < n ) lazy[p] += val;
}

inline void up(int p)
{
    while( p > 1 )
    {
        p >>= 1;
        tree[p] =
            tree[p<<1] + tree[p<<1^1] + k[p]*lazy[p];
    }
}

inline void down(int p)
{
    for(int s=h;s>0;s--)
    {
        int t = p>>s;
        if( lazy[t] != 0 )
        {
            apply(t<<1  , lazy[t]);
            apply(t<<1^1, lazy[t]);
        }
        lazy[t] = 0;
    }
}

void add(int l, int r, num val)
{
    l += n;
    r += n;
    int b0 = l, b1 = r;
    for(; l < r ; l>>=1, r>>=1 )
    {
        if(l&1) apply(l++, val);
        if(r&1) apply(--r, val);
    }
    up(b0); up(b1-1);
}

num query(int l, int r)
{
    num ans = 0; l += n ; r += n;
    down(l); down(r-1);
    for(; l < r ; l>>=1, r>>=1 )
    {
        if(l&1) ans += tree[l++];
        if(r&1) ans += tree[--r];
    }
    return ans;
}

int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d %d", &n, &c);
        memset(tree, 0, sizeof tree);
        memset(lazy, 0, sizeof lazy);
        build();
        while(c--)
        {
            int cmd, p, q; num v;
            scanf("%d %d %d", &cmd, &p, &q);
            p--;
            if( cmd )
                printf("%lld\n", query(p,q));
            else
            {
                scanf("%lld", &v);
                add(p,q,v);
            }
        }
    }
}
