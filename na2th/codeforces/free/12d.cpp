#include<bits/stdc++.h>
using namespace std;
typedef int num;
const int MN = 500001;
int bt[MN], in[MN], rc[MN],n;
int tree[2*MN], p[MN], seen[MN], pend[MN], ps, ss, ans;

bool btLess(int i,int j)
{ return bt[i]==bt[j]? in[i]<in[j]:bt[i]>bt[j]; }

void insert(int p, int val)
{
    p+=n; tree[p] = max(tree[p],val);
    for(;p>1;p>>=1)
        tree[p>>1] = max(tree[p],tree[p^1]);
}

int query(int l)
{
    int r = n, ans = -1, k = 1;
    for(l+=n,r+=n;l<r;l>>=1,r>>=1,k<<=1)
    {
        if(l&1) ans = max(ans, tree[l++]);
        if(r&1) ans = max(ans, tree[--r]);
    }
    return ans;
}

int main()
{
    memset(tree,-1,sizeof tree);
    scanf("%d", &n);
    for(int i=0;i<n;i++)
        scanf("%d",bt+i);
    for(int i=0;i<n;i++)
    {
        scanf("%d",in+i);
        seen[ss++] = in[i];
    }
    for(int i=0;i<n;i++)
        scanf("%d",rc+i),p[i]=i;

    sort(seen,seen+ss);
    ss = unique(seen,seen+ss) - seen;
    sort(p,p+n,btLess);

    for(int i=0;i<n;i++)
    {
        int pos = lower_bound(seen,seen+ss,in[p[i]]) - seen;
        ans += ( query(pos+1) > rc[p[i]] );
        insert( pos, rc[p[i]] );
    }
    printf("%d\n", ans);
}
