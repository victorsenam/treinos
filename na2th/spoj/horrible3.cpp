#include <bits/stdc++.h>
using namespace std;
typedef long long num;

const int N = 1e5;
int n;
num tree[2*N], k[2*N], a[N];
void build()
{
    for(int i=n;i<2*n;i++) k[i] = 1;
    for(int i=n-1;i>0;i--)
        k[i] = k[i<<1] + k[i<<1|1];
}
inline void add(int p, num x)
{
    tree[p] += k[p]*x;
    if(p < n) a[p] += x;
}
void update(int p)
{
    if(p < 1) return;
    if(p < n)  tree[p] = tree[p<<1] + tree[p<<1|1] + k[p]*a[p];
    update(p>>1);
}
void unlazy(int p)
{
    if(p < 1) return;
    unlazy(p>>1);
    if(p >= n) return;
    add(p<<1,a[p]), add(p<<1|1,a[p]);
    a[p] = 0;
}
void add(int l, int r, num x)
{
    if(l >= r) return;
    if(l&1) add(l++, x);
    if(r&1) add(--r, x);
    add(l>>1,r>>1,x);
}
num query(int l, int r)
{
    num loc = 0;
    if(l >= r) return loc;
    if(l&1) loc += tree[l++];
    if(r&1) loc += tree[--r];
    return loc + query(l>>1,r>>1);
}

int c, t;
int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d %d", &n, &c);
        memset(tree, 0, sizeof tree);
        memset(a, 0, sizeof a);
        build();
        while(c--)
        {
            int cmd, p, q; num v;
            scanf("%d %d %d", &cmd, &p, &q);
            p--;
            if( cmd )
            {
                unlazy(p+n);
                unlazy(q+n-1);
                printf("%lld\n", query(p+n,q+n));
            }
            else
            {
                scanf("%lld", &v);
                add(p+n,q+n,v);
                update(p+n);
                update(q+n-1);
            }
        }
    }
}
