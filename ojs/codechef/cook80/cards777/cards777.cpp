#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+2;

map<pair<int, int>, double> mp[N];
int ts;

int main () {
    scanf("%d", &ts);
    while (ts--) {
        double r, b, p;
        scanf("%lf %lf %lf", &r, &b, &p);
        printf("%.20f\n", double(r*p+b*(r+b-p))/double(r+b));
    }
}
