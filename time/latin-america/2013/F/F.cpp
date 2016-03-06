#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define ff first
#define ss second
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const double eps = 1e-9;
const int inf = INT_MAX;
//////////////0123456789
const int N = 100007;
const int modn = 1000000007;

int n, g;
int a, b, d[N], res;

int main() {
    while (scanf("%d %d", &n, &g) != EOF) {

        for (int i = 0; i < n; i++) {
            scanf("%d %d", &a, &b);
            d[i] = b-a;
        }
        sort(d, d+n);

        res = 0;
        for (int i = 0; i < n; i++) {
            if (d[i] < 0) {
                res += 3;
            } else if (g > d[i]) {
                g -= d[i] + 1;
                res += 3;
            } else if (g == d[i]) {
                g = 0;
                res++;
            }
        }
        printf("%d\n", res);
    }

}
