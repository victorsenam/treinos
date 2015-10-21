#include<bits/stdc++.h>
using namespace std;
typedef int num;
num n,t;

int main()
{
    scanf("%d%d", &n, &t);

    if( t == 10 && n == 1 )
    {
        printf("-1\n");
        return 0;
    }

    if( t < 10 )
        printf("%d", t);
    else
        printf("%d", 1);

    for(int i=0;i<n-1;i++)
        printf("%d",0);
}
