#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long num;
const num N = 5000003;
char str[N];
num  aHashLeft[N], aHashRight[N], bHashLeft[N], bHashRight[N], 
     fexp[N], n, ans[N], sum;

const num prime = 1000000009;
const num base  = 259;
inline num mod(num x)
{ return ((x%prime) + prime)%prime; }
void hashify()
{
    aHashLeft[0]  = str[0];
    bHashLeft[0]  = str[0];
    aHashRight[0] = str[0];
    bHashRight[0] = str[0];
    for(n=1;str[n]!=0;n++)
    {
        aHashLeft[n]  = mod(aHashLeft[n-1] + fexp[n]*str[n]);
        aHashRight[n] = mod(base*aHashRight[n-1] + str[n]);

        bHashLeft[n]  = bHashLeft[n-1] + fexp[n]*str[n];
        bHashRight[n] = base*bHashRight[n-1] + str[n];
    }
}

bool isPalindrome(int i)
{
    printf ("%llu %llu\n", fexp[n-1-i]*bHashLeft[i], bHashRight[i]  );

    return ( fexp[n-1-i]*bHashLeft[i] == bHashRight[i]  );
}

int main()
{
    fexp[0] = 1;
    for(int i=1;i<N;i++)
        fexp[i] = fexp[i-1]*base;

    scanf(" %s", str);
    printf("%s\n", str);
    hashify();
    for(int i=0;str[i]!=0;i++)
        if( isPalindrome(i) )
        {
            ans[i] = 1 + ans[i/2];
            printf("[%d]", i);
        }
        else
            ans[i] = 0;
    
    for(int i=0;i<n;i++)
        sum += ans[i];
    printf("%lld\n", sum);
}
