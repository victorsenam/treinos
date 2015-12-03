#include <bits/stdc++.h>
using namespace std;
typedef int num;

int main()
{
    ios::sync_with_stdio(false);
    for( int a = 1; a < 1000; a++ )
        for( int b = a+1; b < 1000; b++ )
            if( a*a + b*b == (1000-a-b)*(1000-a-b) )
                cout << 1LL*a*b*(1000-a-b) << endl;
}
