#include<bits/stdc++.h>
using namespace std;
typedef long long num;
num a, b, c, d, t;

num gcd( num a, num b )
{  
    if( b == 0ull ) return a;
    return (a%b==0) ? b : gcd(b,a%b) ;
}

int main()
{
    scanf("%lld", &t);
    while( t-- > 0 )
    {
        scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
        printf("%lld\n", 1 + gcd(max(a-c,c-a),max(b-d,d-b)) );
    }
}
