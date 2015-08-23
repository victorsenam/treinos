#include <bits/stdc++.h>

using namespace std;

#define N 13

int n;
int a, c[2][N], equi[2], reg[2], maxTri[2];
vector<pair<pair<int, int>, int> > trian;

int buildTri(int i, int * freq, int maxTri) {
    if (maxTri <= 0) return 0;

    int maxVal = 0;
    for (int j = i; j < trian.size(); j++) {
        if (freq[trian[j].first.first]) 
            freq[trian[j].first.first]--;
        else 
            continue;

        if (freq[trian[j].first.second]) 
            freq[trian[j].first.second]--;
        else {
            freq[trian[j].first.first]++;
            continue;
        }

        if (freq[trian[j].second]) 
            freq[trian[j].second]--;
        else {
            freq[trian[j].first.first]++;
            freq[trian[j].first.second]++;
            continue;
        }
/*
        printf("%d(%d) %d(%d) %d(%d)\n", 
            trian[j].first.first+1, freq[trian[j].first.first],
            trian[j].first.second+1, freq[trian[j].first.second],
            trian[j].second+1, freq[trian[j].second]
        );
*/


        maxVal = max(maxVal, buildTri(j, freq, maxTri-1) + 1);

        freq[trian[j].first.first]++;
        freq[trian[j].first.second]++;
        freq[trian[j].second]++;

        if (maxVal == maxTri) return maxVal;
    }

    return maxVal;
}

int main () {
    while (scanf("%d", &n) != EOF && n) {
        for (int i = 0; i < N; i++) c[0][i] = c[1][i] = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a);
            c[i%2][a-1]++;
        }
        equi[0] = equi[1] = reg[0] = reg[1] = 0;

        for (int i = 0; i < N; i++) {
            equi[0] += c[0][i]/3;
            equi[1] += c[1][i]/3;
            c[0][i] %= 3;
            c[1][i] %= 3;
        }

        if (equi[0] > equi[1]) printf("1\n");
        else if (equi[0] < equi[1]) printf("2\n");
        else {
            if (trian.size() == 0) {
                for (int i = 0; i < N; i++)
                    for (int j = i; j < N; j++)
                        for (int k = j; k < N; k++) {
                            if (i == j && j == k) continue;
                            if (k >= j + i + 1) continue;

                            trian.push_back(make_pair(make_pair(i, j), k));
                        }
            }

            maxTri[0] = maxTri[1] = 0;
            for (int i = 0; i < N; i++) {
                maxTri[0] += c[0][i];
                maxTri[1] += c[1][i];
            }

//printf("f0\n");
            reg[0] = buildTri(0, c[0], maxTri[0]/3);
//printf("f1\n");
            reg[1] = buildTri(0, c[1], maxTri[1]/3);

//            printf("%d %d\n", reg[0], reg[1]);

            if (reg[0] > reg[1]) printf("1\n");
            else if (reg[0] < reg[1]) printf("2\n");
            else printf("0\n");
        }
    }
}

