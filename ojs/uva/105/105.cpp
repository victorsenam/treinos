#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e4+7;

int l[N], h[N];
int p[N];
int n;
multiset<int> s;

int main () {
	int i = 0;

	while (scanf("%d %d %d", &l[i], &h[i], &l[i+1]) != EOF) {
		h[i+1] = h[i];
		p[i] = i;
		p[i+1] = i+1;
		i += 2;
	}
	n = i;

	sort(p, p+n, [] (int i, int j) {
		return l[i] < l[j];
	});

	int ls = -1;
	for (int _i = 0; _i < n;) {
		int t = p[_i];
		while (_i < n+n && l[p[_i]] == l[t]) { 
			int i = p[_i];
			if (i&1) {
				s.erase(s.find(h[i]));
			} else {
				s.insert(h[i]);
			}
			_i++;
		}

		int x;
		if (s.empty()) 
			x = 0;
		else
			x = *(prev(s.end()));

		if (x != ls) {
			if (ls != -1)
				printf(" ");
			printf("%d %d", l[t], x);
		}
		ls = x;
	}
	printf("\n");
}
