#include <iostream>
#include <cstdio>
 
using namespace std;
 
int main(){
    int n,
        hours;
    float salary;
    cin >> n;
    cin >> hours;
    cin >> salary;
    salary *= hours;
 
    cout << "NUMBER = " << n << endl;
    cout << "SALARY = U$ ";
    printf("%.2f\n", salary);
}
