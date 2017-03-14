#include<bits/stdc++.h>
using namespace std;
typedef int num;
const int MS = 1<<13;
const int MN = 1002;
num sol[MS][MS];
bool res[MS][MS];
num acc[MN], in[MN];
int n;

num solve(int l, int r)
{
    if( l+r == acc[n-1] ) {
        bool res = ((l==r) || (min(l,r) == 0 && __builtin_popcount(max(l,r)) == 1));
        return res;
    }
    if( sol[l][r] == -1 )
    {
        int i = lower_bound(acc, acc+n, l+r)-acc;
        sol[l][r] = 0;
        num x = in[i+1];
        if( (x <= (r&-r) || r == 0 ) && solve(l, r+x)) {
            res[l][r] = 1;
            sol[l][r] = 1;
        } else if( (x <= (l&-l) || l == 0 ) && solve(l+x, r)) {
            sol[l][r] = 1;
            res[l][r] = 0;
        }
    }
    return sol[l][r];
}

void build (num l, num r) {
    if (l + r == acc[n-1])
        return;
    int i = lower_bound(acc, acc+n, l+r)- acc;
    if (res[l][r]) {
        printf("r");
        build(l,r+in[i+1]);
    } else {
        printf("l");
        build(l+in[i+1],r);
    }
}

int main()
{
    int tc;
    scanf("%d", &tc);
    while(tc--)
    {
        memset(sol, -1, sizeof sol);
        acc[0] = 0;
        scanf("%d", &n);
        if(n==1)
        {
            printf("l\n");
            continue;
        }
        for(int i=0;i<n;i++)
        {
            scanf("%d", in+i);
            acc[i] = acc[i-(i>0)] + in[i];
        }
        if (solve(in[0],0)) {
            printf("l");
            build(in[0],0);
            printf("\n");
        } else
            printf("no\n");
    }
}
