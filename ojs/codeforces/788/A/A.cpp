#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 2e5+8;

ll a[N];
int n;

ll bs;
ll curr;

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%lld", &a[i]);

    bs = 0;
    curr = 0;

    for (int k = 0; k < 2; k++) {
        curr = 0;
        for (int i = 0; i+1 < n; i++) {
            if ((i&1) == k) {
                curr -= abs(a[i] - a[i+1]);
                if (curr < 0)
                    curr = 0;
            } else {
                curr += abs(a[i] - a[i+1]);
                bs = max(bs, curr);
            }
        }
    }

    printf("%lld\n", bs);
}
