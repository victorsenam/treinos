#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long num;

const int N = 1<<18;
num bd[N], aux;
int bds, ok;

int main()
{
    for(int msk=1;msk<N;msk++)
    {
        num guess = 0;
        for(int i=17;i>=0;--i)
        {
            guess *= num(10);
            if(msk&(1<<i))
                guess += 1;
        }
        ok = 1;
        for(int i=0, aux=guess;i<18;i++,aux/=num(10))
            ok &= ( ((msk>>i)&1) == (aux%num(10))  );
        if(ok) bd[bds++] = guess;
    }
    printf("%d\n", bds);
}
