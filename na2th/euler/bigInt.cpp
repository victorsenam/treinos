#include <bits/stdc++.h>
#define pb push_back
#define bi back_inserter
using namespace std;
const int B = 10;
const int bpt = 7;
typedef unsigned short dig;
typedef long long num;
typedef vector<dig> Int;
const Int U(1,1);
const Int Z(1,0);

bool valid(const Int& a)
{
    for(int i=0;i<a.size();i++)
        if(a[i] > 10u) return false;
    return true;
}

void printInt(const Int& a)
{
    assert(valid(a));
    for(int i=a.size()-1;i>=0;--i)
        putchar(48+a[i]);
    putchar('\n');
}

Int str2Int(char * s)
{
    Int ans (0);
    for(int i=0;s[i];i++)
        ans.pb(s[i]-48);
    reverse(ans.begin(),ans.end());
    return ans;
}

Int int2Int(num e)
{
    Int ans(0);
    for(;e;e/=B)
        ans.pb(e%B);
    return ans;
}

num Int2int(const Int& a)
{
    num t = 0;
    for(int i=a.size()-1;i>=0;i--)
        t = t*10 + a[i];
    return t;
}

inline Int normalize(const Int& a)
{
    Int ans(a);
    while(ans.size() > 1 && !ans.back())
        ans.pop_back();
    return ans;
}

bool operator<(const Int& a, const Int& b)
{
    if(a.size() != b.size())
        return a.size() < b.size();
    int i = a.size()-1;
    while(i && a[i] == b[i]) --i;
    return a[i] < b[i];
}

bool operator==(const Int& a, const Int& b)
{
    if(a.size() != b.size()) return false;
    for(int i=0;i<a.size();i++)
        if(a[i] != b[i]) return false;
    return true;
}

Int operator+(const Int& a, const Int& b)
{
    if(b.size() > a.size()) return b+a;
    int carry = 0, partial;
    Int ans (a.size(), 0);
    for(int i=0;i<a.size();i++)
    {
        partial = carry + a[i];
        if(i<b.size()) partial += b[i];
        ans[i] = partial%B;
        carry = partial/B;
    }
    for(;carry;carry/=B) ans.pb(carry%B);
    return ans;
}

Int operator-(const Int& a, const Int& b)
{
    if(a==b) return Z;
    Int ans(a);
    for(int i=0;i<b.size();i++)
    {
        if(b[i] > ans[i])
        {
            int j=i+1;
            for(;!ans[j];j++)
                ans[j] = B-1;
            ans[j]--;
            ans[i] += B;
        }
        ans[i] -= b[i];
    }
    return normalize(ans);
}

Int operator<<(const Int& a, num e)
{
    Int ans (e, 0);
    for(int i=0;i<a.size();i++)
        ans.pb(a[i]);
    return ans;
}

Int halve(const Int& a)
{
    Int ans (0);
    for(int i=0;i<a.size();i++)
        ans.pb(a[i]>>1);
    for(int i=1;i<a.size();i++)
        if(a[i]&1) ans[i-1] += 5;
    return normalize(ans);
}

Int operator*(const Int& a, const Int& b)
{
    if(a.size() < 128 || b.size() < 128)
    {
        Int ans(a.size()+b.size()+1,0);
        for(int i=0;i<a.size();i++)
        {
            int carry = 0;
            for(int j=0;j<b.size();j++)
            {
                int partial = ans[i+j] + a[i]*b[j] + carry;
                ans[i+j] = partial%B;
                carry = partial/B;
            }
            for(int j=0;carry;j++,carry/=B)
                ans[i+j+b.size()] = carry%B;
        }
        return normalize(ans);
    }
    if(b.size() > a.size()) return b*a;
    int d = (b.size())>>1;
    Int a0 (a), a1;
    move(a0.begin()+d, a0.end(), bi(a1));
    a0.erase(a0.begin()+d, a0.end());
    a0 = normalize(a0);

    Int b0 (b), b1;
    move(b0.begin()+d, b0.end(), bi(b1));
    b0.erase(b0.begin()+d,b0.end());
    b0 = normalize(b0);

    Int z1 ((a1+a0)*(b1+b0)),
        z0 (a0*b0), z2 (a1*b1);
    Int ans ((z2<<(2*d)) + ((z1-z2-z0)<<d) + z0);
    return ans;
}

Int operator/(const Int& p, const Int& q)
{
    assert(!(q==Z));
    if(p<q) return Z;
    Int lo (U), hi (p);
    while(lo<hi)
    {
        Int mid (halve(lo+hi+U));
        if( p < mid*q )
            hi = mid - U;
        else
            lo = mid;
    }
    return lo;
}

Int fexp(Int a, long long e)
{
    Int t(U);
    while(e)
    {
        if(e&1) t = t*a;
        a = a*a;
        e>>=1;
    }
    return t;
}

Int operator!(const Int& a)
{
    if(a<U) return U;
    return a*!(a-U);
}

int main()
{
    char in[50];
    int n;
    while(!feof(stdin))
    {
        scanf(" %s%d", in, &n);
        Int a(str2Int(in)<<(2*n)),
            x(U<<n);
        int g = 2*log2(n);
        while(g--)
            x = halve(x+a/x);
        printInt(x);
    }
}
