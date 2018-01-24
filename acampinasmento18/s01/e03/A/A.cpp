#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int n;
map<string,int> mp;
vector<string> ansu;
vector<string> anst;

int main () {
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		string un, tm;
		cin >> un >> tm;

		mp[un]++;

		if (un == "MSU") {
			if (mp[un] > 4) continue;
		} else if (un == "SCH") {
			continue;
		} else if (mp[un] > 2) continue;

		ansu.pb(un);
		anst.pb(tm);
	}

	if (ansu.size() > 10) ansu.resize(10);
	cout << (int) ansu.size() << endl;
	for (int i = 0; i < ansu.size(); i++) {
		cout << ansu[i] << " " << anst[i] << endl;
	}
}
