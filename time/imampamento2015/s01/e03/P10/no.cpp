#include <bits/stdc++.h>

using namespace std;

int v[10], r[10];

void count(int a)
{
    int w = 1;
    memset(v,0, sizeof v);
    for(; a/w > 0; w*= 10)
    {
        for(int i = 0; i < 10; i++)
            v[i] += w*(a/(10*w));
        for(int i=1; i < (a/w)%10; i++)
            v[i] += w;
        if((a/w)%10)
            v[(a/w)%10] += a%w +1;
    }
    //v[0] -= w; v[a%10] --;
}


int main () {
    int a, b;
    while (scanf("%d %d", &a, &b) != EOF && (a||b) ) {
        if(a != b)
        {
            count(b);
            for (int i = 0; i < 10; i++)
                r[i] = v[i];

            count(a-1);
            for (int i = 0; i < 10; i++)
                r[i] -= v[i];
        }
        else
        {
            memset(r,0,sizeof r);
            for(;a > 0; a /= 10)
                r[a%10]++;
        }

        for (int i = 0; i < 10; i++) {
            printf("%d ", r[i]);
        }
        printf("\n");       
    }
}
