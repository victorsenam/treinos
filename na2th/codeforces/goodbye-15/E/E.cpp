#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;

const int N = 2e5; 
int teams[7], ones, left[N], ls;
int a, b, c, n, t;
vector<int> f[3];
int ans;

int main()
{
    scanf(" %d%d%d%d", &n, &a, &b, &c);
    teams[0] = a;   teams[1] = b;   teams[2] = c;
    teams[3] = a+b; teams[4] = a+c; teams[5] = b+c;
    teams[6] = a+b+c;
    sort(teams,teams+7);
    while(n--)
    {
        scanf(" %d", &t);
        if(t > teams[6])
        {
            printf("-1\n");
            return 0;
        }
        int x = lower_bound(teams, teams+7, t) - teams;
        if(x == 6)
            ans++;
        else if(x>2)
            left[ls++] = lower_bound(teams, teams+7, teams[6] - teams[x])-teams, ans++;
        else f[x].push_back(t);
    }
    for(int i=0;i<ls;i++)
    {
        int j = left[i];
        while(j>=0 && !f[j].size()) j--;
        if(j>=0) f[j].pop_back();
    }
    while(42)
    {
        a = b = c = -1;
        for(int i=2;c<0 && i>=0;--i)
            if(f[i].size() > 0)
            {
                c = f[i].back()
                f[i].pop_back();
            }
        for(int i=1;b<0 && i>=0;--i)
            if(f[i].size() > 0)
            {
                b = f[i].back()
                f[i].pop_back();
            }
        if(f[0].size() > 0)
        {
            a = f[0].back();
            f[0].pop_back();
        }
        if(!f[0].size() && !f[1].size() && !f[2].size()) break;
    }
    printf("%d\n", ans);
}
