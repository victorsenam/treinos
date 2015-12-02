#include <bits/stdc++.h>
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;

const int MN = 1e5+3;
int n, k;
num s[MN];

int main()
{
    scanf(" %d%d", &n, &k);
    for(int i=0;i<n;i++)
        scanf(" %I64d", s+i);
    reverse(s,s+n);
    for(int i=k;i<n;i++)
        s[2*k-i-1] += s[i];
    printf("%I64d\n", *max_element(s,s+k));
}
