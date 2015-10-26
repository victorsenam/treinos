#include <bits/stdc++.h>
using namespace std;
typedef int num;
const int MN = 1001;
num tree[2*MN], p[MN], in[MN];
int t, n, ans;

bool inLess(int i,int j)
{ return in[i] == in[j] ? i < j : in[i] < in[j]; }

void insert(int p, int val)
{
    for(tree[p+=n]=val;p>0;p>>=1)
        tree[p>>1] = tree[p] + tree[p^1];
}

int query(int l, int r)
{
    int ans = 0;
    for(l+=n,r+=n;l<r;l>>=1,r>>=1)
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
        scanf(" %d", &n);
        for(int i=0;i<n;i++)
            scanf(" %d", in+i), p[i] = i;
        fill(tree, tree+2*n, 0);
        sort(p,p+n,inLess);
        ans = 0;
        for(int i=0;i<n;i++)
        {
            ans += query(0,p[i]);
            insert(p[i], 1);
        }
        printf("%d\n", ans);
    }
}
