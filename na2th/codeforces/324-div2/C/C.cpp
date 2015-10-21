#include<bits/stdc++.h>
using namespace std;
typedef int num;
const int MS = 100001;
char s1[MS], s2[MS], ans[MS];
int n, t, t1, t2, s, ok;

int main()
{
    scanf("%d%d", &n, &t);

    for(int i=0;i<n;i++)
    {
        scanf(" %c", s1+i);
        ans[i] = s1[i];
    }
    for(int i=0;i<n;i++)
        scanf(" %c", s2+i);

    for(int i=0;i<n;i++)
    {
        if( s1[i] == s2[i] )
            s++;
        else if( t1 > t2 )
            t2++;
        else
            t1++, ans[i] = s2[i];
    }

    if( t1 > t || t2 > t )
    {
        printf("%d\n", -1);
        return 0;
    }

    if( t1 < t2 )
    {
        for(int i=0;i<n;i++)
            if( ans[i] == s1[i] )
            {
                ans[i] = s2[i];
                t1++;t2--;
                break;
            }
    }
    else if ( t2 < t1 )
    {
        for(int i=0;i<n;i++)
            if( ans[i] == s2[i] )
            {
                ans[i] = s1[i];
                t1--;t2++;
                break;
            }
    }

    ok = ( t1 == t2 && t1 == t );
    for(int i=0;!ok && i<n;i++)
        if( s1[i] == s2[i] )
        {
            ans[i] = s1[i] == 'z' ? 'a' : s1[i] + 1;
            t1++; t2++;
            ok |= ( t1 == t2 && t1 == t );
        }

    if(ok)
        printf("%s\n", ans);
    else
        printf("%d\n", -1);
}
