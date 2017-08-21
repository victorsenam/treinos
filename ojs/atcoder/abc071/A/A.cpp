#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int x, a, b;

int main () {
	cin >> x >>a >> b;

	if (abs(x - a) <= abs(x-b)) {
		cout << "A" << endl;
	} else {
		cout << "B" << endl;
	}
}
