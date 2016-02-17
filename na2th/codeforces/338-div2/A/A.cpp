#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define bi back_inserter
#define all(a) a.begin(), a.end()
using namespace std;
typedef long long num;
set<int> seen;

int n, m;
int main()
{
    scanf(" %d%d", &n, &m);
    while(n--)
    {
        int aux, in;
        scanf(" %d", &aux);
        while(aux--)
        {
            scanf(" %d", &in);
            seen.insert(in);
        }
    }
    if(m <= seen.size())
        printf("YES\n");
    else printf("NO\n");
}
