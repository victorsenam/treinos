#include <bits/stdc++.h>
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;

const int MN = 1e5+1;
int n, k, a, ans;

inline int nim(int x)
{
    if( x < 4 ) return x&1;
    if( x == 4 ) return 2;
    if( x&1 ) return 0;
    return 1 + (nim(x>>1) == 1);
}

int main()
{
    scanf(" %d%d", &n, &k);
    ans = 0;
    if(k&1)
    {
        for(int i=0;i<n;i++)
        {
            scanf(" %d", &a);
            ans ^= nim(a);
        }
    }
    else
    {
        for(int i=0;i<n;i++)
        {
            scanf(" %d", &a);
            if(a < 3)
                ans ^= a;
            else
                ans ^= (a-1)&1;
        }
    }
    if(ans)
        printf("Kevin\n");
    else
        printf("Nicky\n");
}
