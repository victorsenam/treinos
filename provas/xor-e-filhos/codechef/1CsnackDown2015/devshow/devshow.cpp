#include <bits/stdc++.h>

using namespace std;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif


#define N 100000

int n, t, a;
int v[N];
int maxi[2]; // 2 melhores
int posi[4][2];
int mai, men;
int res, at;
int out[2];

int main () 
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);

        for (int i = 0; i < n; i++) v[i] = 0;

        for (int i = 0; i < 2*(n - 2); i++)
        {
            scanf("%d", &a);
            a--;
            v[a]++;
        }

        maxi[0] = 0;
        for (int i = 1; i < n-2; i++)
            if (v[maxi[0]] < v[i]) maxi[0] = i;

        maxi[1] = (maxi[0] == 0) ? 1 : 0;

        for( int i = 0; i < n-2; i++)
            if( i != maxi[0] && v[i] > v[maxi[1]] )
                maxi[1] = i;


        v[maxi[0]] += 2;
        res = -1;

        // 0 é o voto de n-2
        // 1 é o voto de n-1

        posi[0][0] = n-1;
        posi[0][1] = n-2;

        posi[1][0] = n-1;
        posi[1][1] = maxi[1];
            
        posi[2][0] = maxi[1];
        posi[2][1] = n-2;

        posi[3][0] = maxi[1];
        posi[3][1] = maxi[1];

        for (int i = 0; i < 4; i++)
        {
            at = 0;
            if (maxi[0] == maxi[1] && i > 0) break;

            v[posi[i][0]]++;
            v[posi[i][1]]++;

            mai = men = v[0];
            for (int j = 1; j < n; j++)
            {
               if (v[j] > mai) mai = v[j];
               if (v[j] < men) men = v[j];
            }

            if (v[n-1] != mai && v[n-1] != men)
                at++;
            if (v[n-2] != mai && v[n-2] != men)
                at++;
    
            if (at > res)
            {
                for (int j = 0; j < 2; j++) 
                    out[j] = posi[i][j];
                res = at;
            }

            v[posi[i][0]]--;
            v[posi[i][1]]--;
        }

        if (res == 2)
            printf("both\n");
        else if (res == 1)
            printf("one\n");
        else
            printf("none\n");

        printf("%d %d\n", maxi[0]+1, out[0]+1);
        printf("%d %d\n", maxi[0]+1, out[1]+1);
    }
}
