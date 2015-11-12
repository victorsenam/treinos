#include <bits/stdc++.h>
using namespace std;
typedef int num;
num get_num()
{
    num s = 1; char c;
    while(isspace(c=getchar()));
    if(!isdigit(c))
        s = -1, c=getchar();
    num ans = c-'0';
    while(isdigit(c=getchar()))
    {
        ans += ans<<2; ans <<= 1;
        ans += c-'0';
    }
    return s*ans;
}
const int MOD = 1e9+7;
struct mod
{
    num x;
    mod () : x(0) {}
    mod (num a) : x(a) {}
    mod operator+(mod b) { return (1ll*x+1ll*b.x)%MOD; }
    mod operator*(mod b) { return (1ll*x*1ll*b.x)%MOD; }
};

int main()
{
}
