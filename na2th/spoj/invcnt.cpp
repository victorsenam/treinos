#include<bits/stdc++.h>
using namespace std;
typedef long long num;
const int MN = 200001;
num tree[2*MN], n, ans;
int in[MN], p[MN];
int tc;

num query(int p)
{
    num ans = 0; int l=0;
    for(l+=n,p+=n;l<p;p>>=1,l>>=1)
    {
        if(l&1) ans += tree[l++];
        if(p&1) ans += tree[--p];
    }
    return ans;
}

void insert(int p)
{
    for(tree[p+=n]=1;p>1;p>>=1)
        tree[p>>1] = tree[p] + tree[p^1];
}

bool inLess(int i, int j)
{ return in[i] == in[j] ? i > j : in[i] < in[j];}

int main()
{
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d", &n);
        for(int i=0;i<2*n;i++)
            tree[i] = 0;
        for(int i=0;i<n;i++)
            scanf("%d", in+i),p[i] = i;
        sort(p,p+n,inLess);
        ans = 0ll;
        for(int i=n-1;i>=0;i--)
        {
            ans += query(p[i]);
            insert(p[i]);
        }
        printf("%lld\n", ans);
    }
}
