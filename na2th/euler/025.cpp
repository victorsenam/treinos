#include <bits/stdc++.h>

using namespace std;
const int BASE = 10;

typedef vector<short> Int;
Int U (1,1), Z (1,0);

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

int digits(Int& a)
{
    int p, dpi, ans;
    dpi = ans = 0;
    for( p = 1; p < BASE; p *= 10, dpi++ );
    for( p = 1; p < a.back() ; p *=10 ) ans++;
    return ans + dpi*(a.size()-1);
}

void printInt(Int& a)
{
    for(int i=a.size()-1;i>=0;i--)
        printf("%d", a[i]);
}

int d, ans;
int main()
{
    Int f0 = Z, f1= U;
    scanf(" %d", &d);
    while(digits(f0) < d)
    {
        f0 = f0 + f1;
        swap(f0, f1);
        ans++;
    }
    printf("%d\n", ans-2);
}
