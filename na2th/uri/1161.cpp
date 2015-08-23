#include <cstdio>

using namespace std;

long long fact(long long n)
{
    return ( n == 0 ) ? 1 : n*fact(n-1);
}

int main()
{
    long long a, b, ans;
    while( scanf("%lld %lld", &a, &b) > 0 )
    {
        ans = 0;
        ans += fact(a);
        ans += fact(b);
        printf("%lld\n", ans);
    }
}
