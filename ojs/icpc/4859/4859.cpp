#include <bits/stdc++.h>

#define N 200000004
#define K 200

using namespace std;

double pre[(N+N/8)+K*K], val;
int mini, maxi, w, l, size;

double calc(int ind) {
    /*
    double ret = pre[ind/K];
    for (int i = ind - ind%K + 1; i <= ind; i++)
        ret += 1.0/((double)i);
    return ret;
    */
    if (ind > 10000)
        return log((double) ind);

    double ret = 0;
    for (int i = 1; i <= ind; i++) {
        ret += 1.0/(double)i;
    }
    return ret;
}

int main () {
    pre[0] = 0.0;
    val = 1.0;
    size = 0;
    /*
    for (int i = 1; i < (N+N/8)+K*K; i++) {
        if (i%K)
            pre[size+1] += 1.0/val;
        else {
            pre[size+2] = pre[size+1] + 1.0/val;
            size++;
        }
        val += 1.0;
    }
    */
    
    int c = 0;
    while (scanf("%d %d", &w, &l) != EOF && (w || l)) {
        printf("Case %d:\n", ++c);
        if (l == 0) {
            if (w%8 == 0)
                printf("On Average Bob Reaches Round 8.00\n");
            else
                printf("Situation Impossible.\n");
        } else {
            mini = l + max(0, (w-7*l+7)/8);
            maxi = l + w/8;

 //           printf("%d %d\n", mini, maxi);
                
            val = (calc(maxi) - calc(mini-1));
 //           printf("%.18f\n", val);
            val = val*(double)(w+l);
//            printf("%.2f\n", val);
            val = val/(double)(maxi-mini+1);
 //           printf("%.18f\n", val);

            printf("On Average Bob Reaches Round %.2f\n", val);
        }
    }
}
