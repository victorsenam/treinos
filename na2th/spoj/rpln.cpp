#include<bits/stdc++.h>
using namespace std;
typedef int num;
const int MT = 100002;
num tree[2*MT];
int n, q, t;

void build()
{
    for(int i=n-1;i>0;i--)
        tree[i] = min( tree[i<<1], tree[i<<1|1] );
}

num query(int l, int r)
{
    num ans = INT_MAX;
    for( l += n, r += n; l < r ; l>>=1, r>>=1 )
    {
        if (l&1) ans = min(ans, tree[l++]);
        if (r&1) ans = min(ans, tree[--r]); 
    }
    return ans;
}

int main()
{
    scanf("%d", &t);
    for(int tc=1;tc<t+1;tc++)
    {
        printf("Scenario #%d:\n", tc);
        scanf(" %d %d", &n, &q);

        for(int i=0;i<2*n;i++)
            tree[i] = INT_MAX;
        for(int i=n;i<2*n;i++)
            scanf("%d", tree+i);

        build();
        for(int i=0;i<q;i++)
        {
            int a, b;
            scanf("%d %d", &a, &b); a--;
            printf("%d\n", query(a,b));
        }
    }
}
