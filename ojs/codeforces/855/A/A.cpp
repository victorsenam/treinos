#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

set<string> s;
string st;
int n;

int main () {
	cin >> n;

	for (int i = 0; i < n; i++)  {
		cin >> st;
		if (s.find(st) != s.end()) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
			s.insert(st);
		}
	}
}
