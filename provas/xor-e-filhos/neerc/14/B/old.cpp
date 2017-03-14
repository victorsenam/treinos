#include <bits/stdc++.h>
using namespace std;
typedef long long num;

const int N = 1e5+2;
const double eps = 1e-9;
int n;
double A, B, a[N], b[N], g[N];
double s0[N], s1[N];
double na, nb, ns, cosab;

int main()
{
    scanf(" %d%lf%lf", &n, &A, &B);
    for(int i=0;i<n;i++)
        scanf(" %lf%lf%lf", g+i, a+i, b+i);
    na = nb = cosab = 0.0;
    for(int i=0;i<n;i++)
    {
        na += a[i]*a[i];
        nb += b[i]*b[i];
        cosab = a[i]*b[i];
    }
    na = sqrt(na);
    nb = sqrt(nb);
    cosab /= na*nb;
    ns = B/(nb*cosab);
    for(int i=0;i<n;i++)
        s0[i] = a[i]*(ns/na);
    double aux = 1;
    for(int i=0;i<n;i++)
        aux = max(aux, s0[i]/g[i]);
    if(aux - 1 > eps)
    {
        for(int i=0;i<n;i++)
        {
            s1[i] = min(s0[i], g[i]);
            s0[i] /= aux;
        }

        double t0 = 0.0, t1 = 0.0;
        for(int i=0;i<n;i++)
            t0 += s0[i]*a[i], t1 += s1[i]*a[i];
        if(t1 > t0)
        {
            for(int i=0;i<n;i++)
                s0[i] = s1[i];
        }
    }
}
