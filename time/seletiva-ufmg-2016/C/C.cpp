#include <bits/stdc++.h>

using namespace std;


int a, n;
int s;

void fail(){
	printf("N\n");
	exit(0);
}

int main () {
	s = 0;

	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &a);

		s += a;
		if (s < 0) fail();
	}

	printf("S\n");
}
