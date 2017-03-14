#include <bits/stdc++.h>

using namespace std;

int freq[28];
char p[28];
int c;

bool cmp_t (int i, int j) {
	if (freq[i] == freq[j])
		return i < j;
	return freq[i] > freq[j];
}

int main () {
	while (scanf("%c", &c) != EOF) {
		if (c < 'A' || c > 'Z') continue;

		freq[c-'A']++;
	}

	for (int i = 0; i <= 'Z'-'A'; i++)
		p[i] = i;

	sort(p, p+'Z'-'A'+1, cmp_t);

	for (int i = 0; i <= 'Z'-'A'; i++)
		printf("%c %d\n", p[i]+'A', freq[p[i]]);
}
