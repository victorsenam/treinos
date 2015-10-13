#include<bits/stdc++.h>
using namespace std;
typedef int num;
const int MN = 10001;
int tree[2*MN], tc, n, u, q;

void update(int l, int r, int val)
{
    for(l+=n,r+=n;l<r;l>>=1,r>>=1)
    {
        if(l&1) tree[l++] += val;
        if(r&1) tree[--r] += val;
    }
}

int query(int p)
{
    int ans = 0;
    for(p+=n;p>0;p>>=1)
        ans += tree[p];
    return ans;
}

int main()
{
    scanf("%d",&tc);
    while(tc--)
    {
        scanf("%d %d",&n,&u);
        for(int i=0;i<2*n;i++)
            tree[i] = 0;
        while(u--)
        {
            int l, r, val;
            scanf("%d %d %d", &l, &r, &val);
            update(l,r+1,val);
        }
        scanf("%d", &q);
        while(q--)
        {
            int tgt;
            scanf("%d", &tgt);
            printf("%d\n", query(tgt));
        }
    }
}
