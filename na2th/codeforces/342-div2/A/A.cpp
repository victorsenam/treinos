#include <bits/stdc++.h>
using namespace std;
typedef long long num;
num n, a, b, c, ans, g;

int main()
{
    cin >> n >> a >> b >> c;
    ans = n/a;

    g = (n-b)/(b-c) + 1ll;
    if(a <= n - b - (g-1ll)*(b-c)) g++;
    ans = max(ans,g);

    g = n - c;
    num x = 1, y = 1;
    while(a*y + (b-c)*x <= n)
    {
        num tx = (g - a*y)/(b-c),
            ty = (g - (b-c)*x)/a;
        if(tx == x && ty == y) break;
        if(tx-x < ty-y) y = ty;
        else x = tx;
    }

    ans = max(ans, x + y);

    cout << ans << endl;
}
