#include <bits/stdc++.h>
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;

num n;
num lo, hi, mid, fix;
int t;

int main()
{
    scanf(" %d", &t);
    while(t--)
    {
        scanf(" %lld", &n);
        for(num k=2;k<num(5e4);k++)
        {
            fix = (k*(k-num(1)))/num(2);
            if(fix > n)
            {
                printf("IMPOSSIBLE\n");
                break;
            }

            lo = 1;
            hi = n;
            while(lo < hi)
            {
                mid = (lo+hi)>>1;
                if(mid*k + fix >= n)
                    hi = mid;
                else
                    lo = mid + 1;
            }
            if(lo*k + fix == n)
            {
                printf("%lld = %lld",n, lo);
                for(int i=1;i<k;i++)
                    printf(" + %lld", lo + num(i));
                putchar('\n');
                break;
            }
        }
    }
}
