#include<bits/stdc++.h>
using namespace std;
typedef long long num;
num ans, a, t;
int n;

int main()
{
    scanf(" %lld", &t);
    while(t--)
    {
        ans = 0;
        scanf(" %d", &n);
        for(int i=0;i<n;i++)
        {
            scanf(" %lld", &a);
            while(a&1) a>>=1;
            ans ^= a;
        }
        if(ans)
            printf("YES\n");
        else
            printf("NO\n");
    }
}
