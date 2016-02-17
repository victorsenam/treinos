#include <bits/stdc++.h>
using namespace std;
typedef long long num;
typedef double cood;
const int N = 2e5+7;

int n, bi, bj, d;
cood bst, g;
num sum[2*N];
int a[N];

num query(int l, int r)
{
    num ans = 0;
    for(l+=n, r+=n;l<r;l>>=1,r>>=1)
    {
        if(l&1) ans += sum[l++];
        if(r&1) ans += sum[--r];
    }
    return ans;
}

int main()
{
    scanf(" %d", &n);
    for(int i=0;i<n;i++) scanf(" %d", a+i);
    sort(a, a+n);

    for(int i=0;i<n;i++) sum[n+i] = a[i]; 
    for(int i=n-1;i>=0;--i) sum[i] = sum[i<<1] + sum[i<<1|1];

    bi = -1;
    bst = query(0, n)/cood(n);
    if(n&1) bst -= a[n/2];
    else    bst -= .5*(a[n/2] + a[n/2-1]);

    for(int i=0;i<n;i++)
    {
        if(i >= n-i) break;

        num S = query(0,i) + query(n-i,n);
        g = (S + a[i])/cood(2*i+1) - cood(a[i]);
        if(g > bst)
        {
            bst = g;
            bi = i;
            d = 0;
        }

        for(int j=i+1; j < n-i;j++)
        {
            if(j-i > 500) break;
            g = (S + a[i] + a[j])/cood(2*i+2) - .5*(a[i] + a[j]);
            if(g > bst)
            {
                bst = g;
                bi = i;
                bj = j;
                d = 1;
            }
        }
    }

    if(bi != -1)
    {
        printf("%d\n", 2*bi + 1 + d);
        for(int i=0;i<=bi;i++)
            printf("%d ", a[i]);

        if(d) printf("%d ", a[bj]);

        for(int i=n-bi;i<n;i++)
            printf("%d ", a[i]);
        putchar('\n');
    }
    else
    {
        printf("%d\n", n);
        for(int i=0;i<n;i++) printf("%d ", a[i]);
        putchar('\n');
    }
}
