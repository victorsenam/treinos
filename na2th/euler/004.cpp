#include <bits/stdc++.h>
using namespace std;
typedef int num;
num in, ans;

num fexp(num x, int r)
{
    num t = 1;
    while( r )
    {
        if( r%2 == 1 ) t *= x;
        x *= x;
        r /= 2;
    }
    return t;
}

bool isPalindrome( num a )
{
    int digits = 0;
    for( num aux = a; aux > 0 ; aux /= 10 )
        digits++;
    digits--;
    while( a > 10 )
    {
        num disp = fexp(10, digits);
        if( a/disp != a%10 )
            return false;
        a -= disp*(a/disp); 
        a /= 10;
        digits -= 2;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> in;
    ans = INT_MIN;
    for( int i = 0; i < in; i++ )
        for( int j = 0; j < in; j++ )
            if( isPalindrome(i*j) && i*j > ans )
                ans = i*j;
    cout << ans << endl;
}
