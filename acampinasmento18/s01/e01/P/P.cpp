#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

deque<int> lst;

void solve(deque<int> pref, deque<int> suf) {
	if(suf.empty()) {
		for(int i = 0; i < pref.size() - 1; i++)
			printf("%d ", pref[i]);
		printf("%d\n", pref.back());
		lst = pref;
		return;
	}
	deque<int> bk = suf;
	pref.pb(bk.front());
	suf.pop_front();
	solve(pref, suf);
	for(int i = 1; i < bk.size(); i++) {
		suf = lst;
		while(suf.size() > bk.size() - 1)
			suf.pop_front();
		for(int &y : suf)
			if(y == bk[i])
				y = bk[i - 1];
		pref.pop_back();
		pref.push_back(bk[i]);
		solve(pref, suf);
	}
}

int main () {
	int n;
	scanf("%d", &n);
	deque<int> all;
	for(int i = 1; i <= n; i++) all.pb(i);
	solve(deque<int>(), all);
}
