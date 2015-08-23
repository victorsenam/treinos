#include<bits/stdc++.h>
using namespace std;
typedef int num;
num n,ans; char plays[2015];

int main()
{
    scanf("%d", &n);
    scanf(" %s", plays);
    for(int i=1; plays[i]!= 0; i++)
        if( i%n == 0 && 
            plays[i-1] == plays[i-2] && 
            plays[i-2] == plays[i-3] )
            ans++;
    printf("%d\n", ans);
}
