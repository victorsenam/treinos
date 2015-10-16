#include <bits/stdc++.h>

using namespace std;

typedef pair<double, double> pdd;

const int N = 1007;

int n[2];
double w;
double x[N];
const double obj[2] = {75.0, 100.0};
pdd att, aux;

int main () {
    while (scanf("%d %d %lf", n, n+1, &w) != EOF && (n[0] || n[1] || w!=0.0)) {
        bool ok = 1;
        for (int k = 0; k < 2; k++) {
            for (int i = 0; i < n[k]; i++)
                scanf("%lf", x+i);

            if (!ok)
                continue;
            sort(x, x+n[k]);

            double ls = 0.0;
            for (int i = 0; ok && i < n[k]; i++) {
                if (x[i]-w/2 > ls)
                    ok = 0;
                ls = max(x[i]+w/2, ls);
            }
            if (ls < obj[k])
                ok = 0;
        }

        if (ok) printf("YES\n");
        else printf("NO\n");
    }
}
