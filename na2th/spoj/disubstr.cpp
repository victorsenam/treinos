#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef long long hsh;
const hsh MOD  = 1000000007ll;
const hsh base = 257ll;
const int MN   = 5003;
char s[MN];
hsh in[MN], powers[MN];
int n, tc, sa[MN], ss, ans;

inline hsh mod ( hsh x )
{ return (x%MOD+MOD)%MOD; }

int lcp(int a, int b)
{
    if( s[a] != s[b] ) return 0;
    int lo = 0,
        hi = n - max(a,b);
    while( lo < hi )
    {
        int mid = lo + (hi-lo)/2;
        if ( mod( (in[a+mid]-in[a-1])*powers[n-a-1] ) !=
             mod( (in[b+mid]-in[b-1])*powers[n-b-1] ) )
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

bool sless(int a, int b)
{
    int p = lcp(a,b);
    return (s[a+p] < s[b+p]);
}

int main()
{
    powers[0] = 1ll;
    for(int i=1;i<MN;i++)
        powers[i] = mod(base*powers[i-1]);
    scanf("%d", &tc);
    while(tc--)
    {
        scanf(" %s", s+1);
        n = strlen(s+1);
        ans = n*(n+1)/2;
        n++; ss = 0;
        in[0] = 0ll;
        for(int i=0;i<n;i++)
        {
            in[i] = mod(in[i-(i>0)] + powers[i]*s[i]);
            sa[ss++]=i;
        }
        sa[0] = 0;
        sort(sa, sa+ss, sless);
        for(int i=0;i<ss-1;i++)
            ans -= lcp(sa[i],sa[i+1]);
        printf("%d\n", ans);
    }
}
