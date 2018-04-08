#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

char c;
int cnt[1000];
char str[5003];

int main () {
	char ls = 'a';
	scanf(" %s", str);
	for (int i = 0; str[i]; i++) {
		char c = str[i];
		cnt[c]++;
		if (c < ls) {
			printf("NO\n");
			return 0;
		}
		ls = c;
	}

	if (cnt['a']*cnt['b']*cnt['c'] && (cnt['c'] == cnt['a'] || cnt['c'] == cnt['b'])) {
		printf("YES\n");
	} else {
		printf("NO\n");
	}
}
