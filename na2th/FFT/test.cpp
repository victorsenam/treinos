#include <bits/stdc++.h>
using namespace std;
typedef long long num;

const int P = 7*17*(1<<23) + 1;
const int g = 3;
const int N = (1<<23);

struct mod
{
    int x;
    mod() : x(0) {}
    mod(int a) : x(a%P) {}
    mod operator+(const mod& b) const { return (num(x)+num(b.x))%P;}
    mod operator*(const mod& b) const { return (num(x)*num(b.x))%P;}
    mod operator-(const mod& b) const { return (num(x)+P-num(b.x))%P;}
};
inline mod fexp(mod x, num e)
{
    mod t(1);
    for(;e;e>>=1, x = x*x)
        if(e&1) t = t*x;
    return t;
}

int n, k;
int p[N];
mod fft[N];

void dft(int * A, int inv)
{
    int r;
    mod w, even, odd, curr;
    for(int i=0;i<n;i++) fft[i] = A[p[i]];
    for(int l=1;l<n;l<<=1)
    {
        r = (P-1)/(l<<1);
        if(inv) r *= (l<<1) - 1;
        w = fexp(g, r);
        for(int i=0;i<n;i+=(l<<1))
        {
            curr = 1;
            for(int j=i;j<i+l;j++, curr = curr*w)
            {
                even = fft[j];
                odd  = fft[j+l];
                fft[j]   = even + curr*odd;
                fft[j+l] = even - curr*odd;
            }
        }
    }
    for(int i=0;i<n;i++) A[i] = fft[i].x;
}

int conv(int * A, int as, int * B, int bs, int * C)
{
    int ans = as + bs - 1;
    k = 32 - __builtin_clz(ans);
    n = 1<<k;
    for(int i=0;i<n;i++)
        p[i] = ((i&1)<<(k-1))|(p[i>>1]>>1);
    for(int i=as;i<n;i++) A[i] = 0;
    for(int i=bs;i<n;i++) B[i] = 0;

    dft(A, 0); dft(B, 0);
    for(int i=0;i<n;i++) C[i] = (mod(A[i])*mod(B[i])).x;
    dft(C, 1);

    mod fix = fexp(n, P-2);
    for(int i=0;i<n;i++) C[i] = (mod(C[i])*fix).x;
    return ans;
}

int A[N], as;
int B[N], bs;
int C[N], cs;

int D[N], ds;
int E[N], es;
int S[N], ss;
int T, K;

inline int rand(int x)
{ return (1.0*rand()/RAND_MAX)*x; }
inline int sgn(int x)
{ return (x > 0) - (x < 0); }
int main()
{
    srand(time(NULL));
    clock_t t;
    t = clock();
    scanf(" %d%d", &T,&K);
    while(clock() - t < T*60*CLOCKS_PER_SEC)
    {
        as = rand(K);
        for(int i=0;i<as;i++)
            A[i] = D[i] = rand(20);
        bs = rand(K);
        for(int i=0;i<bs;i++)
            B[i] = E[i] = rand(20);

        ss = as + bs - 1;
        memset(S, 0, sizeof S);
        for(int i=0;i<as;i++)
            for(int j=0;j<bs;j++)
                S[i+j] += A[i]*B[j];

        cs = conv(A, as, B, bs, C);
        assert(cs == ss);
        for(int i=0;i<ss;i++)
            if(C[i] != S[i])
            {
                printf("\n%d\n", as);
                for(int i=0;i<as;i++)
                    printf("%d ", E[i]);

                printf("\n%d\n", bs);
                for(int i=0;i<bs;i++)
                    printf("%d ", D[i]);

                printf("\n%d\n", ss);
                for(int i=0;i<ss;i++)
                    printf("%d ", S[i]);

                printf("\n%d\n", cs);
                for(int i=0;i<cs;i++)
                    printf("%d ", C[i]);
                putchar('\n');
                return 0;
            }
        putchar('.');
        fflush(stdout);
    }
}
