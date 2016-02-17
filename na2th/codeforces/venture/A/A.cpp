#include <bits/stdc++.h>
using namespace std;
typedef long long num;

int n, ans;
char in[201];

int solve(int p)
{
    int loc = 0;
    int x = 0, y = 0;
    while(p < n)
    {
        if(in[p] == 'L') x--;
        else if(in[p] == 'U') y++;
        else if(in[p] == 'D') y--;
        else x++;
        loc += (x == 0 && y == 0);
        p++;
    }
    return loc;
}

int main()
{
    scanf(" %d", &n);
    scanf(" %s", in);
    for(int i=0;i<n;i++)
        ans += solve(i);
    printf("%d\n", ans);
}
