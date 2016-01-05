#include <bits/stdc++.h>
typedef int num;
using namespace std;
const int Q = 1e5;
int freq[Q], seen[Q], tree[2*Q], x[Q], c[Q];
int q, ss, i;

num gcd(num a, num b)
{ return b ? gcd(b,a%b) : a; }
void insert(int p, num x)
{
    for(tree[p+=ss]=x;p>1;p>>=1)
        tree[p>>1] = gcd(tree[p],tree[p^1]);
}
num query(int l, int r)
{
    num ans = 0;
    for(l+=ss,r+=ss;l<r;l>>=1,r>>=1)
    {
        if(l&1) ans = gcd(ans, tree[l++]);
        if(r&1) ans = gcd(ans, tree[--r]);
    }
    if(ans == 0) ans = 1;
    return ans;
}

int main()
{
    scanf(" %d", &q);
    for(int i=0;i<q;i++)
    {
        char aux;
        scanf(" %c %d", &aux, x+i);
        seen[ss++] = x[i];
        if(aux == '+') c[i] = 1;
        else           c[i] = -1;
    }
    sort(seen, seen+ss);
    ss = unique(seen, seen+ss) - seen;
    for(int k=0;k<q;k++)
    {
        i = lower_bound(seen, seen+ss, x[k]) - seen;
        freq[i] += c[k];
        if(freq[i] > 0) insert(i, x[k]);
        else insert(i, 0);
        printf("%d\n", query(0, ss));
    }
}
