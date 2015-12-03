#include <bits/stdc++.h>
#define mp make_pair
using namespace std;
typedef long long num;

const int N = 1e6;
int p[N], n;
num v[N], lis[2*N];

void insert(int p, num x)
{
    for(lis[p+=n]=x ;p>1; p>>=1)
        lis[p>>1] = max(lis[p],lis[p^1]);
}

num query(int l, int r)
{
    num ans = 0;
    for(l+=n,r+=n;l<r;l>>=1,r>>=1)
    {
        if(l&1) ans = max(ans, lis[l++]);
        if(r&1) ans = max(ans, lis[--r]);
    }
    return ans;
}

bool strict_increasing(int i, int j)
{ return mp(v[i],-i) < mp(v[j],-j); }

bool non_decreasing(int i, int j)
{ return mp(v[i],i) < mp(v[j], j); }

int main()
{
    scanf(" %d", &n);
    for(int i=0; i<n; i++)
    {
        scanf(" %lld", v+i);
        p[i] = i;
    }

    sort(p,p+n,strict_increasing);
    for(int j=0; j<n; j++)
    {
        int i = p[j];
        insert(i, 1 + query(0,i));
    }
    printf("The longest strict increasing sequence has size %d\n", query(0,n));

    fill(lis, lis+2*n, 0);
    sort(p,p+n,non_decreasing);
    for(int j=0; j<n; j++)
    {
        int i = p[j];
        insert(i, 1 + query(0,i));
    }
    printf("The longest non decreasing sequence has size %d\n", query(0,n));
}
