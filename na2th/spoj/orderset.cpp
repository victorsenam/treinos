#include <bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef int edge;

template<typename T>T& getnum(T& t)
{
    char c; T s = 1;
    while(isspace(c=getchar()));
    if(c=='-') s=-1,c=getchar();
    t = c-48;
    while(isdigit(c=getchar())) t = (t<<3)+(t<<1)+c-48;
    return t*=s;
}
template<typename T,typename... Ts> void getnum(T& t, Ts&...ts)
{ getnum(t); getnum(ts...); }

const int Q = 2e5;
num q, x[Q]; char c[Q];
num mask[Q];
num tree[2*Q+3], n;

inline void insert(int p, num x)
{
    for(tree[p+=n]=x; p>1; p>>=1)
        tree[p>>1] = tree[p] + tree[p^1];
}
inline num query(int l, int r)
{
    num ans = 0;
    for(l+=n,r+=n;l<r;l>>=1,r>>=1)
    {
        if(l&1) ans += tree[l++];
        if(r&1) ans += tree[--r];
    }
    return ans;
}
inline int search(int k)
{
    int lo = 0, hi = n, mid;
    while(lo < hi)
    {
        mid = lo + (hi-lo)/2;
        if( query(0,mid+1) >= k ) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int main()
{
    getnum(q);
    n = 0;
    for(int i=0;i<q;i++)
    {
        scanf(" %c%d", c+i,x+i);
        if(c[i] != 'K')
            mask[n++] = x[i];
    }
    sort(mask, mask+n);
    n = unique(mask, mask+n) - mask;
    for(int i=0;i<q;i++)
    {
        num val = lower_bound(mask,mask+n,x[i]) - mask;
        if( c[i] == 'I' || c[i] == 'D' ) insert(val, c[i]=='I');
        else if ( c[i] == 'C' ) printf("%d\n", query(0,val));
        else
        {
            if( query(0,n) < x[i] )
                printf("invalid\n");
            else
                printf("%d\n", mask[search(x[i])]);
        }
    }
}
