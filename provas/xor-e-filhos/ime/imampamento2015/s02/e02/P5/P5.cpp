#include<bits/stdc++.h>
#define MN 100002
using namespace std;
typedef long long int num;
num n, a[MN];

num gcd(num a, num b)
{ return ( a%b == 0 ) ? b : gcd(b,a%b); }

num solve(num s, num e, num &d, num &siz)
{
    if( e == s )
    {
        d = a[e];
        siz = 1;
        return d*siz;
    }
    num dl, sizl, bl, dr, sizr, br, dmid;
    bl = solve(s, (s+e)/2, dl, sizl);
    br = solve((s+e)/2+1, e, dr, sizr);
    // b-right vira brecursive
    if( br < bl )
    {
        br = bl; sizr = sizl; dr = dl;
    }
    dmid = gcd(a[(s+e)/2], a[(s+e)/2+1]);
    num f = (s+e)/2,
        l = (s+e)/2+1, nf[2], nl[2], nd[2], x;
    while( f>s && a[f-1]%dmid == 0 ) f--;
    while( l<e && a[l+1]%dmid == 0 ) l++;
    x = 0;
    while( s < f || l < e )
    {
        nf[x] = f; nl[x] = l;
        // 0 esquerda 1 direita
        if( x == 0 && f == s )
        {
            nf[0] = nl[0] = 1;
            nd[0] = -1;
            x^=1; continue;
        }
        else if( x == 0 ) nd[x] = gcd(dmid, a[f-1]);
        else if( l == e ) break;
        else nd[x] = gcd(dmid, a[l+1] );

        while( nf[x] > s && a[nf[x]-1]%nd[x] == 0 ) nf[x]--;
        while( nl[x] < e && a[nl[x]+1]%nd[x] == 0 ) nl[x]++;

        if( x == 1 )
        {
            if( (nl[0]-nf[0]+1)*nd[0] < (nl[1]-nf[1])*nd[1] )
            {
                nl[0] = nd[1];
                nf[0] = nf[1];
                nd[0] = nd[1];
            }
            if( (l-f+1)*dmid <= (nl[0]-nf[0]+1)*nd[0] )
            {
                dmid = nd[0];
                f = nf[0];
                l = nl[0];
                x = 0;
            }
            else break;
        }
        x^=1ll;
    }
    if( br < dmid*(l-f+1) )
    {
        d = dmid;
        siz = (l-f+1);
    }
    else
    {
        d = dr;
        siz = sizr;
    }
    return d*siz;
}

int main()
{
    int tc; scanf("%d", &tc);
    while( tc-- > 0 )
    {
        num d, siz;
        scanf("%lld", &n);
        for(int i=0;i<n;i++)
            scanf("%lld", a+i);
        printf("%lld\n", solve(0,n-1,d, siz));
    }
}
