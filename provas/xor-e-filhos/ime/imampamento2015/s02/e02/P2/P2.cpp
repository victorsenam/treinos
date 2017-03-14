#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

#define N 5000009

const num p = 1000000009;
const num base = 259;
num aHashLeft[N], aHashRight[N],
    bHashLeft[N], bHashRight[N], fexp[500], fs;
char str[N], deg[N];
num n;

inline num mod(num x)
{ return (x%p + p)%p; }

void hashifyLeft()
{
    num ans=0;
    aHashLeft[0] = str[0]+1;
    bHashLeft[0] = str[0]+1; ans++;
    for(; str[ans] != 0; ans++)
    {
        aHashLeft[ans] = mod(aHashLeft[ans-1] + fexp[ans%fs]*(str[ans]+1));
        bHashLeft[ans] =     bHashLeft[ans-1] + fexp[ans%fs]*(str[ans]+1);
    }
    n = ans;
}

void hashifyRight()
{
    aHashRight[0] = str[n-1]+1;
    bHashRight[0] = str[n-1]+1;
    for(int i=1;i<n;i++)
    {
        aHashRight[i] = mod(aHashRight[i-1] + fexp[i%fs]*(str[n-i-1]+1));
        bHashRight[i] =     bHashRight[i-1] + fexp[i%fs]*(str[n-i-1]+1) ;
    }

}

inline bool isPal(int i)
{
    return 
    //( aHashLeft[i] == (aHashRight[]-aHashRight[i+1])/fexp[(i+1)%fs] ) &&
        ( bHashLeft[i] == bHashRight[i] );
}

int main () {
    scanf(" %s", str);
    num res = 0;

    fs=0;
    fexp[fs++] = 1;
    while( fexp[fs-1] < base*fexp[fs-1] )
    {
        fexp[fs] = fexp[fs-1]*base;
        fs++;
    }

    hashifyLeft();
    hashifyRight();
    for(int i=0;i<n;i++)
        printf("%lld ", aHashLeft[i]);
    printf("\n");
    for(int i=0;i<n;i++)
        printf("%lld ", aHashRight[i]);
    printf("\n");
    for(int i=0;i<n;i++)
        printf("%lld ", bHashLeft[i]);
    printf("\n");
    for(int i=0;i<n;i++)
        printf("%lld ", bHashRight[i]);
    printf("\n");

    deg[0] = res = 1;
    printf("[%d]\n", n);
    for (int i = 1; str[i] != '\0'; i++) {
        if (!isPal(i))
            deg[i] = 0;
        else {
            deg[i] = deg[i/2]+1;
            printf("%d\n", i);
        }
        res += deg[i];
    }

    printf("%llu\n", res);
}
