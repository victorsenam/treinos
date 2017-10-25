#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 103;

ll s, n, k;

ll a[N];

int main () {
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	sort(a, a+n);

	for (int i = 0; i < k; i++)
		s += a[i];
	
	cout << (s + 99)/100 << endl;
}
