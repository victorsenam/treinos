#include <bits/stdc++.h>
using namespace std;
typedef int num;
const int MD = 200;
const int B  = 10;

short ans[MD], aux[MD], spc[MD], as, is;

void increment()
{
    short carry = 1;
    for(int i=0; i < is; i++)
    {
        num partial = aux[i] + carry;
        aux[i] = partial%B;
        carry  = partial/B;
    }
    while(carry)
    {
        aux[is++] = carry%B;
        carry /= B;
    }
}

void multiply()
{
    memset(spc, 0, sizeof spc);
    short carry; num partial;
    for(int i=0;i<as;i++)
    {
        carry = 0;
        for(int j=0;j<is; j++)
        {
            num partial = carry + spc[i+j] + ans[i]*aux[j];
            spc[i+j] = partial%B;
            carry    = partial/B;
        }
        spc[i+is] = carry;
    }
    memcpy(ans, spc, sizeof spc);
    for(as=MD-1;!ans[as];--as); as++;
}

int n, tot;
int main()
{
    scanf(" %d", &n);
    aux[0] = ans[0] = as = is = 1;
    for(int i=0;i<n;i++, increment())
        multiply();
    for(int i=0;i<as;i++)
        tot += ans[i];
    printf("%d\n", tot);
}
