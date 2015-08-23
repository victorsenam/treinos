#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    float classes[5] = {0,400,800,1200, 2000};
    float raise[5] = { 0.15, 0.12, 0.10, 0.07, 0.04};
    vector<int> v(classes, classes+5);
    float salary;
    int lb = 0;

    cin >> salary;
    if(salary == 0)
        lb = 0;
    else
        lb = lower_bound(v.begin(), v.end(), salary) - v.begin() - 1;

    printf("Novo salario: %.2f\n", ( (1 + raise[lb])*salary ) );
    printf("Reajuste ganho: %.2f\n", (raise[lb])*salary );
    cout << "Em percentual: " << raise[lb]*100 << " %\n" ;

    return 0;
}
