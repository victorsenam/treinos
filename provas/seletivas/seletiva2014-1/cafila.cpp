#include <cstdio>

int main () {
    int     NC, ND, MC, MD, WC, WD, i;
    double  PD, PC,
            P0, P1, P2, sum,
            EQD, EQC,
            ETD, ETC;

    while (scanf("%d %d %d %d %d %d", &ND, &NC, &MD, &MC, &WD, &WC) != EOF) {
        PD = (double) WD/(WD+WC);
        PC = (double) WC/(WD+WC);

        P0 = PC*PC*PC;
        P1 = 3*PD*PC*PC;
        P2 = 3*PD*PD*PC;
        sum = P0 + P1 + P2;
        P0 /= sum;
        P1 /= sum;
        P2 /= sum;

        EQC = 3*P0 + 2*P1 + P2;
        EQD = P1 + 2*P2;

        ETC = 0;
        for (i = 1; i < MC; i++) {
            ETC += 1.0/(double)(MC-i);
        }
        ETC *= NC;

        ETD = 0;
        for (i = 1; i < MD; i++) {
            ETD += 1.0/(double)(MD-i);
        }
        ETD *= ND;
        
        printf("%f %f\n", ETC/EQC, ETD/EQD);

        if (ETC/EQC > ETD/EQD) printf("%.3lf", ETC/EQC);
        else printf("%.3lf", ETD/EQD);
    }
}
