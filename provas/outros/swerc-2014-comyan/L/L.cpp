#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long num;
const int MN = 33;
num ans[MN];
int t, aux;

int main()
{
    ans[1] = 1ll;
    for(int i=2;i<MN;i++)
        ans[i] = 2ll*ans[i-1] + 1ll;
    scanf("%d", &t);
    while(t--)
    {
        scanf(" %d", &aux);
        printf("%llu\n", ans[aux]);
    }
}
