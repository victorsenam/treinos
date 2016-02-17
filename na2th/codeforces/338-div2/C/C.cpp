#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define bi back_inserter
#define all(a) a.begin(), a.end()
using namespace std;
typedef long long num;
const int S = 3002;

int n, m, ans;
char in[S], ni[S], goal[S];
set<char> seen;

int main()
{
    scanf(" %s", in);
    n = strlen(in);
    for(int i=n-1;i>=0;--i)
        seen.insert(ni[n-1-i] = in[i]);
    scanf(" %s", goal);
    m = strlen(goal);
    for(int i=0;i<m;i++)
        if(!seen.count(goal[i]))
        {
            printf("-1\n");
            return 0;
        }
    i = 0;
}
