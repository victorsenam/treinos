#include <bits/stdc++.h>
using namespace std;
typedef long long num;

int small[20] = {0, 3, 3, 5, 4, 4, 3, 5, 5, 4, 3, 
                 6, 6, 8, 8, 7, 7, 9, 8, 8},
      big[10] = {0, 0, 6, 6, 5, 5, 5, 7, 6, 6};

inline int count(int x)
{
    if(x<20) return small[x];
    return big[x/10] + small[x%10];
}

int tot, loc, aux;
int main()
{
    tot = 0;
    for(int c=0;c<10;c++)
        for(int d=0;d<100;d++)
            tot += small[c] + count(d) + (c>0)*7 + (c>0 && d>0)*3;
    tot += 11;
    printf("%d\n", tot);
}
