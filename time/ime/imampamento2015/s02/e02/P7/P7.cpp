#include<bits/stdc++.h>
#define MN 100002
using namespace std;
typedef int num;

num tree[MN], n, m;

void insert(int p, num val)
{
    for(; p>0;p-=(p&-p))
        tree[p] += val;
}

num count(int p)
{
    num ans = 0;
    for(;p<=n;p+=(p&-p))
        ans += tree[p];
    return ans;
}

int main()
{
    int tc; scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d %d", &n, &m);
        for(int i=0;i<n+1;i++)
            tree[i] = 0;
        insert(n,n-1);
        for(int i=1;i<n;i++)
            insert(i, -1);
        for(int i=1;i<n+1;i++)
            printf("[%d]", count(i));
        for(int i=0;i<m;i++)
        {
            num aux; scanf("%d", &aux);
            num val = count(aux);
            printf("%d ", val);
            insert(n, 1);
            insert(aux, -val-1);
            insert(aux-1, val+1);
        }
    }
}
