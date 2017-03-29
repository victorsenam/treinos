#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

double d, l, v1, v2;

int main () {
    scanf("%lf %lf %lf %lf", &d, &l, &v1, &v2);

    printf("%.20f\n", (l-d)/(v1+v2));
}
