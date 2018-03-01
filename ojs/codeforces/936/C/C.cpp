#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e3+7;
int n;

char inp[N];
char oup[N];

int main () {
	scanf("%d", &n);
	scanf(" %s", inp);
	scanf(" %s", oup);
	cout << oup << endl << endl;
	cout << inp << endl;

	vector<int> res;

	for (int i = n-1, s = 0; i >= 0; i--, s++) {
		int j = i;

		while (j >= 0 && inp[j] != oup[s]) j--;
		if (j < 0) {
			printf("-1\n");
			return 0;
		}

		res.pb(n-j-1);
		res.pb(1);
		res.pb(n-1);

		for (int k = j+1; k < n; k++)
			swap(inp[k-1],inp[k]);
		reverse(inp, inp+j);

		cout << inp << endl;
	}

	printf("%d\n", (int) res.size());
	for (int x : res)
		printf("%d ", x);
	printf("\n");
}
