#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e4+7;

int ts;
int n, w, l;
int p[N];
int r[N];

int solve (int m) {
	r[n] = 0;
	int j = n;
	for (int i = n-1; i >= 0; i--) {
		while (p[i] + m <= p[j-1])
			j--;

	}
}

int main () {
}
