#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;

string str[N];
int cnt[500];
int my[500];
int n;

int main () {
	cin >> n;

	int res = 0;
	for (int i = 0; i < n; i++) {
		cin >> str[i];

		cnt[str[i][0]]++;
	}

	for (int i = 0; i < n; i++) {
		cnt[str[i][0]]--;
		for (int j = 0; j < str[i].size(); j++)
			my[str[i][j]]++;

		bool ok = 1;
		for (int a = 'a'; a <= 'z'; a++) {
			if (my[a] > cnt[a])
				ok = 0;
			my[a] = 0;
		}

		cnt[str[i][0]]++;

		if (ok)
			res++;
	}
	cout << res << endl;
}
