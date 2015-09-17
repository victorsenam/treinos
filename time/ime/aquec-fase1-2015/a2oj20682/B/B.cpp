#include<bits/stdc++.h>
using namespace std;
typedef long long num;
typedef int point;
const int MN = 100002;
num x[MN], y[MN];
int n, s[MN], ans[MN], ss;

num cross(point a, point b, point c)
{ return (x[c]-x[b])*(y[a]-y[b]) - (y[c]-y[b])*(x[a]-x[b]); }

int main()
{
    int tc;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d", &n);
        memset(ans, 0, sizeof ans);
        ss = 0;
        for(int i=0;i<n;i++)
        {
            scanf("%lld %lld", x+i, y+i);
            while ( ss > 2 && cross(s[ss-1], s[ss-2], i) <= 0ll )
                ans[s[--ss]-1] = i;
            s[ss++] = i;
        }
        for(int i=0;i<2*n;i++)
            printf("%d ", ans[i]);
        printf("\n");
    }
}
