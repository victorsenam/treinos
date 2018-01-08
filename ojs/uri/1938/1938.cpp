#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 3e3+7;
const int K = 20;

deque<int> qu;
int n;
int sp[N][K];
vector<pii> v[N];

int main () {
	scanf("%d", &n);
	
	for (int i = 0; i < n; i++)
		scanf("%d %d", &v[i].first, &v[i].second);
	sort(v.begin(), v.end());

	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < n; i++) {
			int x = v[i].second;
			auto it = lower_bound(qu.begin(), qu.end(), x);

			if (it != qu.begin()) {
				--it;
				res += 
			}
		}
	}
}
