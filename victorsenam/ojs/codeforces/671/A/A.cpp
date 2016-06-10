#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define lld I64d
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 1000007;

double p[3][2];
double t[N][2];
double sum, res;
int mini;
int n;

double sq (double a) {
    return a*a;
}
double dist (int i, int j) {
    return sqrt(sq(t[j][0]-p[i][0]) + sq(t[j][1]-p[i][1]));
}

int main () {

    for (int i = 0; i < 3; i++)
        scanf("%lf %lf", &p[i][0], &p[i][1]);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &t[i][0], &t[i][1]);
        sum += dist(2, i)*2.;
    }

    res = 1./0.;
    if (n == 1) {
        for (int k = 0; k < 2; k++)
            res = min(res, dist(k, 0) + dist(2, 0));
    } else {
        for (int k = 0; k < 2; k++) {
            mini = 0;
            for (int i = 1; i < n; i++) 
                if (dist(k, i) - dist(2, i) < dist(k, mini) - dist(2, mini))
                    mini = i;
            res = min(res, sum - dist(2, mini) + dist(k, mini));
            for (int i = 0; i < n; i++) {
                if (i == mini) continue;

                res = min(res, sum - dist(2, mini) - dist(2, i) + dist(k, mini) + dist(k^1, i));
            }
        }
    }

    printf("%.20f\n", (double(res)));
    
}
