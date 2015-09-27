#include<bits/stdc++.h>
using namespace std;
typedef int num;
const int MP = 1000003;
num n, d;
num h[MP], p[MP], sunk[MP], ans, q, done;

bool permLess(int a, int b)
{ return h[a] < h[b]; }

int main()
{
    int tc;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d %d", &n, &d);
        ans = 1; done = 0;
        sunk[0]   = 1;
        sunk[n+1] = 1;
        for(int i=1;i<n+1;i++)
        {
            scanf("%d", h+i);
            p[i-1]    = i;
            sunk[i]   = 0;
        }
        sort(p,p+n,permLess);
        for(int i=0;i<d;i++)
        {
            scanf("%d", &q);
            while( done < n && h[p[done]] <= q )
            {
                num left  =  p[done]-1,
                    right =  p[done]+1;
                if( sunk[left] && sunk[right] )
                    ans--;
                else if( !sunk[left] && !sunk[right] )
                    ans++;

                sunk[p[done]] = 1;
                done++;
            }
            if(i) printf(" ");
            printf("%d", ans);
        }
        printf("\n");
    }
}
