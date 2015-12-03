#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long num;
num ans, last, n, in;

int main()
{
    ios::sync_with_stdio(false);
    cin >> in;
    ans = 1; last = 1; n = 1;
    while( ans < in )
    {
        num aux  = n+1,
            curr = 1;
        for( int i = 2; i <= n+1; i++ )
            if( aux%i == 0 )
            {
                num ct = 0;
                while( aux%i == 0 )
                {
                    aux /= i;
                    ct++;
                }
                if( i == 2 )
                    curr *= ct;
                else
                    curr *= (ct+1);
            }
        ans  = last*curr;
        last = curr; n++;
    }
    cout << (n-1)*n/2 << endl;
}
