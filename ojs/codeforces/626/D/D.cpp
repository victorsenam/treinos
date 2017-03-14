#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef double num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 2003;
const int M = 5004;

int a[N];
double prob[M];
double p[M];
double acc[M];
int n;

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", a+i);
    sort(a, a+n);

    int top = a[n-1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            prob[abs(a[i]-a[j])] += (1./n)*(1./(n-1));
        }
    }

    for (int i = 0; i <= top; i++)
        for (int j = 0; j <= i; j++)
            p[i] += prob[j]*prob[i-j];

    double ans = 0.;
    for (int i = 0; i <= top; i++)
        for (int j = i+1; j <= top; j++)
            ans += p[i]*prob[j];
    printf("%.20f\n", ans);
}
