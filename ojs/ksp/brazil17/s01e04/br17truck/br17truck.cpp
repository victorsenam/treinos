#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

double dist[112];
const int M = 1123;
int a[M], b[M], c[M];
const double eps = 1e-11;

int main () {
    int i, n, mm, k;
    scanf("%d %d", &n, &mm);
    for(i = 0; i < mm; i++)
        scanf("%d %d %d", &a[i], &b[i], &c[i]), a[i]--, b[i]--, c[i] = -c[i];
    double l = -1.1e6, r = 1.1e6;
    for(int bb = 0; bb < 80; bb++) {
        double m = (l + r) / 2.;
        memset(dist, 0, sizeof dist);
        for(k = 0; k < n; k++)
            for(i = 0; i < mm; i++)
                dist[b[i]] = min(dist[b[i]], dist[a[i]] + c[i] - m);
        bool has = false;
        for(i = 0; i < mm; i++)
            if(dist[b[i]] > dist[a[i]] + c[i] - m + eps)
                has = true;
        if(has) r = m;
        else l = m;
    }
    printf("%.20f\n", -l);
}
