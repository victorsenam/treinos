#include <bits/stdc++.h>
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;
template<typename T>T& getnum(T& t)
{
    char c; T s=1;
    while(isspace(c=getchar_unlocked()));
    if(feof(stdin)) exit(0);
    if(c=='-') s=-1,c=getchar_unlocked(); t = c-48;
    while(isdigit(c=getchar_unlocked())) t = (t<<3)+(t<<1)+c-48;
    return t*=s;
}
template<typename T, typename... Ts> void getnum(T& t,Ts&...ts)
{ getnum(t); getnum(ts...); }

const int MN = 1e3+5;
const double eps = 1e-9;
num n, k;
num w[MN], x[MN];
num W[MN], X[MN];
num a[MN], b[MN];
int lines[MN];
num S[MN][MN];
int qf, qb, ls;

inline double intercept(int i, int j)
{ return 1.*(b[j]-b[i])/(a[i]-a[j]); }
int main()
{
    while(getnum(n,k),1)
    {
        X[0] = W[0] = 0;
        for(int i=1;i<n+1;i++)
        {
            getnum(x[i],w[i]);
            W[i] = W[i-1] + w[i];
            X[i] = X[i-1] + w[i]*x[i];
        }
        S[1][1] = ls = 0;
        for(int i=2;i<n+1;i++)
            S[1][i] = x[i]*W[i-1] - X[i-1];

        for(int q=2;q<k+1;q++)
        {
            qb = qf = ls = 0;
            a[ls]   = -W[q-1];
            b[ls] =  X[q-1];
            lines[qb++] = ls++;
            for(int i=q;i<n+1;i++)
            {
                // S[q][i] = min(j<i) { S[q-1][j] + X[j] - W[j]*x[i] }
                while( qb - qf > 1 && intercept(lines[qf],lines[qf+1]) < double(x[i]) + eps ) qf++;
                S[q][i] = b[lines[qf]] + a[lines[qf]]*x[i];

                a[ls] = -W[i];
                b[ls] = S[q-1][i] + X[i];
                while( qb - qf > 0 && intercept(lines[qb-1], ls) < intercept(lines[qb-2],lines[qb-1]) + eps ) qb--;
                lines[qb++] = ls++;

                S[q][i] += x[i]*W[i-1] - X[i-1];
            }
        }
        printf("%lld\n", S[k][n]);
    }
}
