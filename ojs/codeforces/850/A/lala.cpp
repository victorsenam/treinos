#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int K = 28;
const int N = (1<<K);

char memo[N];

int main () {
	memo[0] = 0;
	for (int i = 1; i < N; i++) {
		if (i%2 == 0) continue;
		if (__builtin_popcount(i) == 2) {
			memo[i] = 0;
			continue;
		}
		int s = 0;
		int c = i;
		int j, r, v;
	
		//cout << bitset<K>(i).to_string() << endl;
		while (c) {
			j = (c&-c);
			r = ((i&(j-1)) | ((i/(j+j))));
			r >>= __builtin_ctz(r);
			//cout << "using " << j << " -> " << bitset<K>(r).to_string() << " " << int(memo[r]) << endl;
			s |= (1<<memo[r]);
			c -= j;
		}

		s++;
		memo[i] = __builtin_ctz(s);
	}
	printf("%d\n", memo[N-1]);
}
