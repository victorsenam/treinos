#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e6+7;

set<char> neigh[400];
char str[N];
char to[N];
char vow[] = "AEIOU";
char con[] = "BCDFGHJKLMNPQRSTVWXYZ";

bool isOk (int i) {
	if (i < 0) return 0;
	char a = str[i];
	return (a >= 'A' && a <= 'Z');
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("javanese.in", "r", stdin);
	freopen("javanese.out", "w", stdout);
#endif

	int n = 0;
	while (true) {
		fgets(str+n, N, stdin);
		if (feof(stdin)) break;
		n += strlen(str+n);
	}

	for (int i = 0; str[i]; i++) {
		for (int k = -1; k <= 1; k += 2) {
			if (isOk(i+k)) neigh[str[i]].insert(str[i+k]);
		}
	}

	assert(strlen(con) + strlen(vow) == 26);

	for (char a = 'A'; a <= 'Z'; a++)
	for (char b = a+1; b <= 'Z'; b++)
	for (char c = b+1; c <= 'Z'; c++)
	for (char d = c+1; d <= 'Z'; d++)
	for (char e = d+1; e <= 'Z'; e++) {
		set<char> s;
		s.insert(a); s.insert(b); s.insert(c); s.insert(d); s.insert(e);
		int vs = 0, cs = 0;
		for (int i = 'A'; i <= 'Z'; i++) {
			for (char n : neigh[i]) if ((s.find(n) != s.end()) == (s.find(i) != s.end())) {
				goto fim;
			}
		}
		for (int i = 0; str[i]; i++) {
			if (isOk(i)) {
				if (!to[str[i]]) {
					if (s.find(str[i]) != s.end()) {
						to[str[i]] = vow[vs++];
					} else {
						to[str[i]] = con[cs++];
					}
				}
				putchar(to[str[i]]);
			} else {
				putchar(str[i]);
			}
		}
		return 0;
fim:
		s.clear();
	}

	printf("impossible\n");
}
