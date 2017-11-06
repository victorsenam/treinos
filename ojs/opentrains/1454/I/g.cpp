#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <ctime>
#include <cstring>
#include <cassert>
#include <bitset>
#include <sstream>
#include <queue>

#define pb push_back
#define mp make_pair
#define fs first
#define sc second
#define sz(a) ((int) (a).size())
#define eprintf(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

typedef long long int64;
typedef long double ldb;

const long double eps = 1e-9;
const int inf = (1 << 30) - 1;
const long long inf64 = ((long long)1 << 62) - 1;
const long double pi = acos(-1);

template <class T> T sqr (T x) {return x * x;}
template <class T> T abs (T x) {return x < 0 ? -x : x;}

const int MAXN = 1000 * 1000 + 100;
int P = 1000 * 1000 * 1000 + 7;

int sum (int a, int b) {
    return (a + b) % P;
}

int mult (long long a, long long b) {
    return (a * b) % P;
}

int deg (int a, int n) {
    if (n == 0)
        return 1;

    int ans = deg(a, n / 2);
    ans = mult(ans, ans);
    if (n % 2 == 1)
        ans = mult(ans, a);

    return ans;
}

int inv (int a) {
    return deg(a, P - 2);
}


int p[MAXN], num[MAXN], fact[MAXN];
bool used[MAXN];

int main () {
//  ios_base::sync_with_stdio(0);
	freopen("galois.in", "rt", stdin);
	freopen("galois.out", "wt", stdout);

    int n;
    scanf ("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf ("%d", &p[i]);
        p[i]--;
    }

    fact[0] = 1;
    for (int i = 0; i < n; ++i) {
        fact[i + 1] = mult(fact[i], i + 1);
    }

    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            int cur_num = 0;
            int cur_v = i;
            do {
                used[cur_v] = true;
                cur_num++;
                cur_v = p[cur_v];
            } while (cur_v != i);
            num[cur_num]++;
        }
    }

    int ans = 1;
    for (int i = 1; i <= n; ++i) {
        if (num[i] != 0) {
            ans = mult(mult(ans, deg(i, num[i])), fact[num[i]]);
        }
    }

    bool div_2 = false;
    for (int i = 1; i <= n; ++i) {
        if (num[i] > 1 || (i % 2 == 0 && num[i] > 0)) {
            div_2 = true;
        }
    }

    if (div_2) {
        ans = mult(ans, inv(2));
    }

    printf ("%d\n", ans);
	return 0;
}
