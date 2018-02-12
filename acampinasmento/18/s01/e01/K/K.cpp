#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

deque<int> lst_print;

void solve(deque<int> fixed, deque<int> all, deque<int> fst) {
	sort(fst.begin(), fst.end());
	sort(all.begin(), all.end());
	//for(int x : fixed) printf("%d ", x);
	//printf("| ");
	//for(int x : all) printf("%d ", x);
	//printf("| ");
	//for(int x : fst) printf("%d ", x);
	//printf("\n");
	if(all.empty() || fst.empty()) {
		for(int i = 0; i < fixed.size() - 1; i++)
			printf("%d ", fixed[i]);
		printf("%d\n", fixed.back());
		lst_print = fixed;
		return;
	}
	int i = 0;
	while(all[i] != fst[0] && i < all.size()) i++;
	assert(i < all.size());
	swap(all[i], all[0]);
	assert(!all.empty());
	all.pop_front();
	sort(all.begin(), all.end());
	fixed.push_back(fst.front());
	assert(!fst.empty());
	fst.pop_front();
	solve(fixed, all, fst);
	while(!all.empty()) {
		set<int> s;
		for(int x : fixed) s.insert(x);
		fst.clear();
		for(int x : lst_print)
			if(!s.count(x))
				fst.pb(x);
		sort(fst.begin(), fst.end());
		if(fst.front() == all.front()) {
			// aaaaa
			// add um cara que nao esta em fst
			s.clear();
			for(int x : fst) s.insert(x);
			bool any = false;
			for(int x : all)
				if(!s.count(x)) {
					fst.pb(x);
					any = true;
					break;
				}
			if(!any) return;
		} else {
			fst.pb(all.front());
		}
		sort(fst.begin(), fst.end());
		assert(fst.front() == all.front());
		assert(!fst.empty());
		fst.pop_front();
		assert(!fixed.empty());
		fixed.pop_back();
		fixed.push_back(all.front());
		assert(!all.empty());
		all.pop_front();
		solve(fixed, all, fst);
	}
}

int main () {
	int i, n, k;
	scanf("%d %d", &n, &k);
	deque<int> all, fst;
	for(i = 1; i <= n; i++) all.pb(i);
	for(i = 1; i <= k; i++) fst.pb(i);
	solve(deque<int>(), all, fst);
}
