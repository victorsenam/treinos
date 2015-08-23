#include<bits/stdc++.h>
using namespace std;
typedef int num;
const num MN = 1001;
const num MT = 366;

num st[MN], en[MN], val[MN],
    perm[MN], sol[MN][MT][MT], n,
    solved[MN][MT][MT];
int TIME;

bool lexLess(int a, int b)
{ return (en[a]==en[b]) ? st[a]<st[b] : en[a] < en[b]; }

num solve(int p, num af, num bf)
{
    // Garanto que af <= bf
    if( af > bf ) return solve(p, bf, af);

    // Garanto que p <= n e ainda ha tempo
    if( p == n || af >= MT ) return 0;

    // Garanto que não calculei ainda
    if( solved[p][af][bf] != TIME )
    {
        num ans = solve(p+1,af,bf);

        if( st[perm[p]] >= bf )
            ans = max(ans,
            val[perm[p]] + max( solve(p+1, en[perm[p]]+1, bf), solve(p+1, en[perm[p]]+1, af) ) );
        else if ( st[perm[p]] >= af )
            ans = max(ans, val[perm[p]] + solve(p+1, en[perm[p]]+1, af) );

        sol[p][af][bf]    = ans;
        sol[p][bf][af]    = ans;
        solved[p][af][bf] = TIME;
        solved[p][bf][af] = TIME;
    }
    return sol[p][af][bf];
}

int main()
{
    TIME = 1;
    while( scanf("%d", &n) != EOF && n )
    {
        for(int i=0;i<n;i++)
        {
            scanf("%d %d %d", st+i, en+i, val+i);
            perm[i] = i;
        }
        sort(perm, perm+n, lexLess);
        printf("%d\n", solve(0,0,0));
        TIME++;
    }
}
