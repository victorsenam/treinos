#include <bits/stdc++.h>
using namespace std;
typedef long long num;

int n;
int c[3], d;
char in;

int main()
{
    scanf(" %d", &n);
    for(int i=0;i<n;i++)
    {
        scanf(" %c", &in);
        if(in == 'B') c[0]++;
        if(in == 'G') c[1]++;
        if(in == 'R') c[2]++;
    }
    for(int i=0;i<3;i++) d += c[i] > 0;

    if(d == 3) printf("BGR\n");
    else if(d == 2)
    {
        for(int i=0;i<3;i++)
        {
            int ok = 0;
            if(c[i])
            {
                for(int j=0;j<3;j++)
                    ok |= (i != j && c[j] > 1);
            }
            else ok = !!c[(i+1)%3]*c[(i+2)%3];
            if(ok) putchar("BGR"[i]);
        }
        putchar('\n');
    }
    else
    {
        for(int i=0;i<3;i++) if(c[i]) putchar("BGR"[i]);
        putchar('\n');
    }
}
