#include <bits/stdc++.h>
using namespace std;
typedef int num;
num n, min1, max1, min2, max2, min3, max3;

int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    cin >> min1 >> max1;
    cin >> min2 >> max2;
    cin >> min3 >> max3;

    n -= min1 + min2 + min3;
    if( n > 0 )
    {
        num change = min(max1-min1, n);
        n -= change;
        min1 += change;
    }
    if( n > 0 )
    {
        num change = min(max2-min2, n);
        n -= change;
        min2 += change;
    }
    if( n > 0 )
    {
        num change = min(max3-min3, n);
        n -= change;
        min3 += change;
    }
    cout << min1 << " " << min2 << " " << min3 << endl;
}
