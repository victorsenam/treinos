#include <cstdio>

using namespace std;

int main(int argc, const char *argv[])
{
    float n1,n2,n3,n4,grade,exam;
    scanf("%f %f %f %f", &n1, &n2, &n3, &n4);
    grade = 2*n1 + 3*n2 + 4*n3 + n4;
    grade *= 0.1;
    printf("Media: %.1f\n", grade);

    if( grade >= 5 && grade < 7 ){
        printf("Aluno em exame.\n");
        scanf("%f", &exam);
        printf("Nota do exame: %.1f\n", exam);
        grade = (grade + exam)*0.5;
        
        if( grade >= 5.0 )
            printf("Aluno aprovado.\n");
        else
            printf("Aluno reprovado.\n");

        printf("Media final: %.1f\n", grade);
    }
    else if( grade >= 7.0 )
        printf("Aluno aprovado.\n");
    else
        printf("Aluno reprovado.\n");
}
