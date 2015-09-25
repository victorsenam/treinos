#include<bits/stdc++.h>
using namespace std;
typedef int num;
const int MN = 100002;
int tc, n, m;
int pos[MN];
int curr, tree[4*MN], ts;

void insert(int p, int val)
{
    for( tree[p+=ts]=val;p>1;p>>=1 )
        tree[p>>1] = tree[p] + tree[p^1];
}

int query(int l, int r)
{
    int ans = 0;
    for(l+=ts,r+=ts;l<r;l>>=1,r>>=1)
    {
        if(l&1) ans += tree[l++];
        if(r&1) ans += tree[--r];
    }
    return ans;
}

int main()
{
    scanf("%d", &tc);
    while(tc--)
    {
        memset(tree, 0, sizeof tree);
        scanf("%d %d", &n, &m);
        ts = n + m;
        for(int i=0;i<n;i++)
        {
            pos[i] = n-i-1;
            tree[n-i-1+ts] = 1;
        }
        for(int i=ts-1;i>0;i--)
            tree[i] = tree[i<<1] + tree[i<<1|1];

        curr = n;
        while(m--)
        {
            int tgt;
            scanf("%d", &tgt); tgt--;
            printf("%d", query(pos[tgt],ts)-1);
            if(m) printf(" ");
            insert(pos[tgt], 0);
            pos[tgt] = curr;
            insert(curr++, 1);
        }
        printf("\n");
    }
}
