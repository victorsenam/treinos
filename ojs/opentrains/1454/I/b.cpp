#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 777;                                
int n, x[N], y[N], vx[N], vy[N], row[N], col[N], row_pair[N], col_pair[N], a[N][N], min_pos[N], p[N], opt_col, opt_row, opt_delta, cur_row;
bool used_col[N], used_row[N];

int ask(int i, int j) {
	return a[i][j] + row[i] + col[j];
}

int main() {
	freopen("banach.in", "r", stdin);
	freopen("banach.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d%d", &x[i], &y[i]);
	for (int i = 0; i < n; ++i)
		scanf("%d%d", &vx[i], &vy[i]);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			a[i][j] = -(x[i] * vx[j] + y[i] * vy[j]);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			row[i] = max(row[i], -a[i][j]);
	for (int i = 0; i < n; ++i)
		row_pair[i] = col_pair[i] = -1;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			used_col[j] = used_row[j] = false, min_pos[j] = i;
		used_row[i] = true, p[i] = -1;
		while (row_pair[i] == -1) {
			opt_col = -1;
			for (int j = 0; j < n; ++j)
				if (!used_col[j] && ((opt_col == -1) || (ask(min_pos[j], j) < ask(min_pos[opt_col], opt_col))))
					opt_col = j;
			opt_row = min_pos[opt_col], opt_delta = ask(opt_row, opt_col);
			for (int j = 0; j < n; ++j) {
				if (used_row[j]) row[j] -= opt_delta;
				if (used_col[j]) col[j] += opt_delta;
			}
			if (col_pair[opt_col] == -1) {
				while (opt_row != -1) {
					col_pair[opt_col] = opt_row;
					swap(row_pair[opt_row], opt_col);
					opt_row = p[opt_row];
				}
			} else {
				cur_row = col_pair[opt_col], p[cur_row] = opt_row;
				used_row[cur_row] = used_col[opt_col] = true;
				for (int j = 0; j < n; ++j)
					if (!used_col[j] && (ask(min_pos[j], j) > ask(cur_row, j)))
						min_pos[j] = cur_row;
			}
		}
	}
	printf("Yes\n");
	for (int i = 0; i < n; ++i)
		printf("%d%c", row_pair[i] + 1, " \n"[i == n - 1]);
	return 0;
}
