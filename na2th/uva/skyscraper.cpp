#include<bits/stdc++.h>
#define MAX 101
using namespace std;
typedef int num;
num f, e, ia, ib, t;
num r[MAX], a0[MAX];
bool gg;

num euclid(num a, num * x, num b, num * y)
{
    num d, ix, iy;
    if(a%b == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }
    d = euclid(b, &ix, a%b, &iy);
    *x = iy;
    *y = ix - iy*(a/b); 
    return d;
}

int main()
{
    scanf("%d", &t);
    while( t-- > 0 )
    {
        scanf("%d %d %d %d", &f, &e, &ia, &ib);
        for( int i = 0; i < e; i++ )
            scanf("%d %d", r+i, a0+i);

        gg = false;
        queue<int> reach;
        set<int> seen;
        reach.push( ia );
        seen.insert( ia );
        while( !gg && !reach.empty() )
        {
            num curr = reach.front(); reach.pop();
            if( curr == ib )
            {
                gg = true;
                break;
            }
        }
    }
}
