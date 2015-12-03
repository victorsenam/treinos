#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long num;
num ans;
int in;

inline num mdc( num a, num b )
{ return ( a%b == 0 )? b : mdc(b, a%b); }

inline num mmc( num a, num b )
{ return a*b/mdc(a,b); }

int main()
{
    ios::sync_with_stdio(false);
    ans = 1;
    cin >> in;
    for( int i = 2; i <= in; i++ )
        ans = mmc(ans, i);
    cout << ans << endl;
}
