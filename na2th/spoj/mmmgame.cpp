#include <bits/stdc++.h>
using namespace std;
typedef long long num;
int n, ans, a, pi, t;

int main()
{
    scanf(" %d", &t);
    while(t--)
    {
        scanf(" %d", &n);
        ans = 0;
        pi = 0;
        for(int i=0;i<n;i++)
        {
            scanf(" %d", &a);
            ans ^= a;
            if(a == 1)
                pi++;
        }
        if(pi != n)
        {
            if(ans)
                printf("John\n");
            else 
                printf("Brother\n");
        }
        else
        {
            if(n&1)
                printf("Brother\n");
            else
                printf("John\n");
        }
    }
}
