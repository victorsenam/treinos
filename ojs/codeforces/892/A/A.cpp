#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back


int n;
vector<int> a,b;

int main () {
	cin >> n;

	int sum = 0;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		sum += a;
	}
	int pm = 0, sm = 0;
	for (int i = 0; i < n; i++) {
		int b;
		cin >> b;

		if (b > pm) {
			sm = pm;
			pm = b;
		} else if (b > sm) {
			sm = b;
		}
	}

	if (sm + pm >= sum)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
}
