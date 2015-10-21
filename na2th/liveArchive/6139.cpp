#include<bits/stdc++.h>
using namespace std;
typedef int num;
const int MN = 100001;
int tree[2*MN];
int n, k;

inline int sign(int x)
{ return ((!!x)*(1-2*(x<0))); }

void insert(int p, int val)
{
    for(tree[p+=n]=sign(val);p>1;p>>=1)
        tree[p>>1] = sign(tree[p]*tree[p^1]);
}

int query(int l, int r)
{
    int ans = 1;
    for(l+=n,r+=n;l<r;l>>=1,r>>=1)
    {
        if(l&1) ans = sign(ans*tree[l++]);
        if(r&1) ans = sign(ans*tree[--r]);
    }
    return ans;
}

char out(int x)
{
    if(x > 0)
        return '+';
    if(!x) return '0';
    return '-';
}

int main()
{
    while( scanf("%d %d", &n, &k) != EOF )
    {
        for(int i=n;i<2*n;i++)
        {
            scanf("%d",tree+i);
            tree[i] = sign(tree[i]);
        }
        for(int i=n-1;i>0;i--)
            tree[i] = sign(tree[i<<1]*tree[i<<1|1]);
        while(k--)
        {
            char cmd;
            int a1,a2;
            scanf(" %c %d %d", &cmd, &a1, &a2);
            a1--;
            if(cmd == 'C')
                insert(a1, a2);
            else
                printf("%c", out(query(a1,a2)));
        }
        printf("\n");
    }
}
