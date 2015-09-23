#include<bits/stdc++.h>
using namespace std;
typedef int num;
const int MP = 1000001;
set<pair< pair<int,int>, int> > sol[1001];
int n, x, y;

int main()
{
    scanf("%d", &n);
    for(int i=0;i<n;i++)
    {
        scanf("%d %d", &x, &y);
        sol[y/1000].insert(make_pair(make_pair(x,y), i));
    }
    for(int i=0;i<1001;i++)
        if(i&1)
            for(auto it = sol[i].rbegin();it!=sol[i].rend();++it)
                printf("%d ", it->second+1);
        else
            for(auto it = sol[i].begin();it!=sol[i].end();++it)
                printf("%d ", it->second+1);
    printf("\n");
}
