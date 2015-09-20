#include<bits/stdc++.h>
using namespace std;
typedef int num;
const int MS = 20007;
int lo[MS],hi[MS],id[MS],p[20][MS], sa[MS];
char s[MS];
int n, tc, ans;

bool lexLess(int a,int b)
{ return lo[a]==lo[b] ? hi[a]<hi[b] : lo[a]<lo[b]; }
bool lexEq(int a,int b)
{ return lo[a]==lo[b] && hi[a]==hi[b]; }

void build()
{
    for(int i=0;i<n;i++)
        p[0][i] = s[i];
    for(int i=0;i<20;i++)
        p[i][n] = -1;
    for(int k=1;k<20;k++)
    {
        for(int i=0;i<n;i++)
        {
            lo[i] = p[k-1][i];
            hi[i] = p[k-1][min(i+(1<<(k-1)),n)];
            id[i] = i; sa[i] = i;
        }
        sort(sa,sa+n,lexLess);
        for(int i=0;i<n;i++)
            p[k][id[sa[i]]] = i && lexEq(sa[i],sa[i-1]) ?
            p[k][id[sa[i-1]]]: i ;
    }
    for(int i=0;i<n;i++)
        sa[p[19][i]] = i;
}

int main()
{
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%s", s);
        n = strlen(s);
        for(int i=n;i<2*n;i++)
            s[i] = s[i-n];
        n *= 2;
        s[n++] = CHAR_MAX;
        s[n++] = 0;
        build();
        printf("%d\n", sa[1]+1);
    }
}
