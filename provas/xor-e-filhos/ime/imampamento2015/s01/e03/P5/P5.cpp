#include <bits/stdc++.h>

using namespace std;

#define N 1007

map<pair<int, int>, int> mp;
map<pair<int, int>, int>::iterator it;
int d[N], f[N];
int l, k, n;

int pd (int i, int w)
{
    if (w > l) return INT_MIN;
    if (i >= n) return 0;
    it = mp.find(make_pair(i,w));
    if (it != mp.end())
        return it->second;

    it = mp.insert(make_pair(make_pair(i,w), max(
        pd(i+1, max(w-k, 0)),
        pd(i+1, w+d[i]) + f[i]        
    )).first;

    return it->second;
}

int main ()
{
    while(scanf("%d %d %d", &n, &k, &l) != EOF && n && k && l)
    {
        for (int i = 0; i < n; i++)
            scanf("%d %d", f+i, d+i);

        printf("%d\n", pd(0, 0));
    }
}
