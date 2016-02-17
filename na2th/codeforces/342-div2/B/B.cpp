#include <bits/stdc++.h>
#define mp make_pair
using namespace std;
typedef long long num;
const int S = 2e5;

int ans, ss, n, m;
char s[S], p[32];
pair<int, int> seen[S];
int lo, hi;

int main()
{
    scanf(" %s %s", s, p);
    n = strlen(s);
    m = strlen(p);

    for(int i=0;i<n;i++)
    {
        int j=i;
        while(j < n && j-i < m && s[j] == p[j-i]) j++;
        if(j-i == m) seen[ss++] = mp(i,j-1);
    }

    int i = 0;
    while(i < ss)
    {
        ans++;
        hi = seen[i++].second;
        while(i < ss && seen[i].first <= hi) i++;
    }

    printf("%d\n", ans);
}
