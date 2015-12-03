#include <bits/stdc++.h>
using namespace std;
typedef int num;
num carry, n, as, in, partial, sum, ans[200];

int main()
{
    ios::sync_with_stdio(false);
    memset( ans, 0, sizeof ans );
    ans[0] = 1;
    as = 1;

    cin >> in;
    for( n = 1; n <= in ; n++ )
    {
        carry = 0;
        for( int i = 0; i < as; i++ )
        {
            cout << n << "*" << ans[i] << endl;
            partial = n*ans[i] + carry;

            ans[i] = partial%10;
            carry = partial/10;
        }
        if( carry )
            ans[as++] = carry;
    }
    for( int i = 0; i < as; i++ )
        cout << ans[as-i-1];
    cout << endl;

    sum = 0;
    for( int i = 0; i < as; i++ )
        sum += ans[i];
    cout << sum << endl;
}
