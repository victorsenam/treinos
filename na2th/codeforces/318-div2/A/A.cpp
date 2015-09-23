#include <bits/stdc++.h>
using namespace std;
typedef int num;
const int MN = 102;
num n, m, a[MN], f[1001], mf, ans;

int main()
{
    scanf("%d", &n);
    mf = -1;
    for(int i=0;i<n;i++)
    {
        scanf("%d", a+i);
        if(i)
        {
            f[a[i]]++;
            mf = max(mf, a[i]);
        }
    }
    while( mf > a[0] )
    {
        while( mf >= 0 && f[mf] == 0 )
            mf--;
        ans++;
        a[0]++;
        f[mf]--;
        f[mf-1]++;
    }
    if( mf == a[0] && f[mf] > 0 )
        ans++;
    printf("%d\n", ans);
}
