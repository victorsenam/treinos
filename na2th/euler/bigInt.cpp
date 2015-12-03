#include <bits/stdc++.h>

#define BASE 1000000000

using namespace std;

typedef vector<int> Int;
Int U (1,1), Z (1,0);

bool operator<(Int a, Int b)
{
    Int::iterator ap, bp;
    if( a.size() < b.size() )
        return true;
    if( a.size() > b.size() )
        return false;
    ap = a.end(); ap--;
    bp = b.end(); bp--;
    while( *ap == *bp && ap != a.begin() && bp != b.begin() )
    {
        ap--;
        bp--;
    }
    return *ap < *bp;
}

bool operator==(Int a, Int b)
{
    Int::iterator ap, bp;
    if( a.size() != b.size() )
        return false;
    ap = a.end(); ap--;
    bp = b.end(); bp--;
    while( *ap == *bp && ap != a.begin() && bp != b.begin() )
    {
        ap--;
        bp--;
    }
    return *ap == *bp;
}

Int operator+(Int a, Int b)
{
    int t, ap, bp;
    long partial, carry;
    Int ans;
    ap = bp = carry = 0;
    t = min( a.size(), b.size() );

    while( ap < t )
    {
        partial = a[ap++] + b[bp++] + carry;
        ans.push_back(partial%BASE);
        carry = partial/BASE;
    }

    while( ap < a.size() )
    {
        partial = a[ap++] + carry;
        ans.push_back(partial%BASE);
        carry = partial/BASE;
    }

    while( bp < b.size() )
    {
        partial = b[bp++] + carry;
        ans.push_back(partial%BASE);
        carry = partial/BASE;
    }

    if( carry )
        ans.push_back( carry );

    return ans;
}

// Assume que a > b
Int operator-(Int a, Int b)
{
    if( a == b ) return Z;
    Int ans;
    long partial;
    int t, u;

    ans.resize( a.size() );
    t = min( a.size(), b.size() );

    for( int p = ans.size() - 1; p >= t; p-- )
        ans[p] = a[p];

    t--;
    while( t >= 0 )
    {
        ans[t] = a[t] - b[t];
        u = t;
        while( ans[u] < 0 )
        {
            ans[u] += BASE;
            ans[++u]--;
        }
        t--;
    }

    while( !ans.back() ) ans.pop_back();

    return ans;
}

Int operator*(Int a, Int b)
{
    Int ans (a.size()+b.size(), 0);
    long partial, carry;
    for( int i = 0; i < a.size(); i++ )
    {
        carry = 0;
        for( int j = 0 ; j < b.size(); j++ )
        {
            partial = (long)a[i]*b[j] + ans[i+j] + carry;
            ans[i+j] = partial%BASE;
            carry = partial/BASE;
        }
        ans[i+b.size()] = carry;
    }

    if( !ans.back() ) ans.pop_back();
    return ans;
}

Int operator^(Int a, long e)
{
    Int t;
    if( !e )
    {
        t.push_back(1);
        return t;
    }
    if( e == 1 )
        return a;
    t = a^(e/2);
    return t*t*(a^(e%2));
}

Int operator!(Int a)
{
    if( a == Z )
        return U;
    return a*(!(a-U));
}

// Assume que *p tem uma string terminada em \0 só formada de numeros
Int str2Int(char * in)
{
    Int ans;
    int partial, 
        n = strlen(in),
        c = 0;

    while( c < n )
    {
        partial = 0;
        for(int p = 1; p < BASE && c < n; p *= 10 )
            partial += p*(in[n-1-c++] - 0x30);
        ans.push_back(partial);
    }

    return ans;
}

int digits(Int a)
{
    int p, dpi, ans;
    dpi = ans = 0;
    for( p = 1; p < BASE; p *= 10, dpi++ );
    for( p = 1; p < a.back() ; p *=10 ) ans++;
    return ans + dpi*(a.size()-1);
}

int main()
{
    Int t;
    char input[100];
    scanf("%s", input);
    t = str2Int(input);
    t = !t;
    printInt(t); printf("\n[%d]\n", digits(t) );
}
