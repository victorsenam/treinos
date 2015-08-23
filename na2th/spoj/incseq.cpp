#include<bits/stdc++.h>
using namespace std;
typedef int num;
const int MS = 10005;
const int MOD = 5000000;
num in[MS], perm[MS], tree[2][MS], n, k, curr;

inline num mod(num x)
{ return (x%MOD + MOD)%MOD; }

void insert(int i, int p, num val)
{
    for(;p<=n;p+=(p&-p))
        tree[i&1][p] = mod(tree[i&1][p] + val);
}

num count(int i, int p)
{
    num sum = 0;
    for(;p>0;p-=(p&-p))
        sum = mod(sum + tree[i&1][p]);
    return sum;
}

num freq(int i, int p)
{
    num ans = tree[i&1][p],
        goal = p - (p&-p);
    if( p-- > 0 )
        for(; p > goal; p-=(p&-p))
            ans = mod(ans - tree[i&1][p]);
    return ans;
}

bool permLess(int a, int b)
{ return ( in[a] == in[b] ) ? a > b : in[a] < in[b] ; }

int main()
{
    scanf("%d %d", &n, &k);
    curr = 1;
    for(int i=1;i<n+1;i++)
    {
        scanf("%d", in+i);
        perm[i-1]  = i;
        tree[curr][i] = (i&-i);
    }
    sort(perm, perm+n, permLess);
    while( curr < k )
    {
        int next = curr + 1;
        for(int i=0;i<n;i++)
        {
            insert(curr, perm[i], mod(-1*freq(curr,perm[i])));
            insert(next, perm[i], mod(count(curr,n) - count(curr, perm[i])) );
        }
        curr++;
    }
    printf("%d\n", mod(count(curr, n)));
}
