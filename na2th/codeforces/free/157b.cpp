#include<bits/stdc++.h>
using namespace std;
const int MP = 101;
const double pi = acos(-1.0);

set<int> radii;
int n, r, s;
double ans = 0.0;
int main()
{
    scanf("%d", &n);
    while( n-- > 0 )
    {
        scanf("%d", &r);
        radii.insert(r);
    }

    for( auto it = radii.rbegin(); it != radii.rend(); ++it )
    {
        r = *it;
        if( s )
            ans -=  pi*r*r;
        else
            ans +=  pi*r*r;
        s ^= 1;
    }
    printf("%lf\n", ans);
}
