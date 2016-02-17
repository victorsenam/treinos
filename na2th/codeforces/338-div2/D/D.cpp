#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define bi back_inserter
#define all(a) a.begin(), a.end()
using namespace std;
typedef long long num;
const int MOD = 1e9+7;
struct mod
{
    int x;
    mod(): x(0) {}
    mod(int a): x(a%MOD) {};
    mod operator+(const mod& b) { return (num(x)+num(b.x))%MOD; }
    mod operator*(const mod& b) { return (num(x)*num(b.x))%MOD; }
};
map<int, int> freq;
int m, in;
num e, prt;
mod ans, n;

mod fexp(mod a, num e)
{
    mod t = 1;
    while(e)
    {
        if(e&1) t = t*a;
        a = a*a;
        e >>= 1;
    }
    return t;
}

int main()
{
    n = ans = 1;
    scanf(" %d", &m);
    while(m--)
    {
        scanf(" %d", &in);
        freq[in]++;
        n = n*in;
    }
    int par = 1;
    for(auto it=freq.begin(); it!=freq.end(); ++it)
        par &= (it->second%2 == 0);
    if(par)
    {
        for(auto it=freq.begin(); it!=freq.end(); ++it)
        {
            int p = it->first, k = it->second/2;
            mod aux = 1;
            while(k--)
                aux = mod(p)*aux;
            ans = ans*aux;
        }
    }
    int f = 1;
    e = 1;
    for(auto it=freq.begin(); it!=freq.end();++it)
    {
        int k = it->second+1;
        if(!(k%2) && f)
            k /= 2, f--;
        e = (e*num(k))%num(MOD-1);
    }
    if(par) e>>=1;
    printf("%d\n", (ans*fexp(n, e)).x);
}
