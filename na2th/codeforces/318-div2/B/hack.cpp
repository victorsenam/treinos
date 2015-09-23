#include<bits/stdc++.h>
using namespace std;
typedef int num;

int main()
{
    int n = 4000,
        m = n, j;
    printf("%d %d\n", n, m);
    j = 0;
    while( m > 0 )
    {
        for(int i=0;m>0 && i<n;i++)
        {
            printf("%d %d\n", j+1, i+1 );
            m--;
        }
        j++;
    }
}
