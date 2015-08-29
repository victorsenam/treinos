#include<bits/stdc++.h>
#define MAX 101
using namespace std;
int s, m;
char men[MAX], mai[MAX];

int main()
{
    scanf("%d %d", &m, &s);
    if( s > 9*m )
    {
        printf("%d %d\n", -1, -1);
        return 0;
    }
    if( s == 0 )
    {
        if( m == 1 )
            printf("%d %d\n", 0, 0);
        else
            printf("%d %d\n", -1, -1);
        return 0;
    }
    for(int i=0;i<m;i++)
    {
        mai[i] = men[m-1-i] = min(9, s) + 0x30;
        s -= mai[i] - 0x30;
    }
    mai[m] = men[m] = 0;
    
    if( men[0]=='0' )
    {
        men[0] = '1';
        for(int i=1;i<m;i++)
            if( men[i] != '0' )
            {
                men[i]--; break;
            }
    }
    printf("%s %s\n", men, mai);
}
