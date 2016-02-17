#include<bits/stdc++.h>
#define mp make_pair
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;

const int N = 1e5+2;
int sol[N], p[N], a[N], b[N], n, ans;

bool aless(int i, int j)
{ return mp(a[i], i) < mp(a[j], j); }

int solve(int i)
{
    if(sol[i] != -1)
        return sol[i];
    sol[i] = 1;
    int k = p[i];
    if(a[k]-a[p[0]] <= b[k]) return sol[i];
    int lo = 0, hi = i-1;
    while(lo<hi)
    {
        int mid = lo + (1+hi-lo)/2;
        if(a[k] - a[p[mid]] <= b[k])
            hi = mid-1;
        else lo = mid;
    }
    sol[i] += solve(lo);
    return sol[i];
}

int main()
{
    memset(sol, -1, sizeof sol);
    scanf(" %d", &n);
    for(int i=0;i<n;i++)
        scanf(" %d%d", a+i, b+i), p[i] = i;
    sort(p, p+n, aless);
    ans = 0;
    for(int i=0;i<n;i++)
        ans = max(ans, solve(i));
    printf("%d\n", n-*max_element(sol,sol+n));
}
