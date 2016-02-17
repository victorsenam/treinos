#include <bits/stdc++.h>
using namespace std;
typedef long long num;

int monthLength(int i)
{
    if(i == 1) return 29;
    if(i < 7) return 30 + !(i%2);
    return 30 + !((i-7)%2);
}
int x, ans;
char k;

int main()
{
    int st = 5;
    scanf(" %d of %c%*s", &x, &k);
    if(k == 'm')
    {
        for(int i=0;i<12;i++)
            ans += (monthLength(i) >= x);
    }
    else
        ans = 52 + (x==5 || x==6);
    cout << ans << endl;
}
