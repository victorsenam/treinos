#include <iostream>
#include <cstring>

using namespace std;

int fibonacci[50];

int fib( int n, int *fib ){
    if( fibonacci[n] != -1 )
        return fibonacci[n];
    fibonacci[n] = fibonacci[n-2] + fibonacci[n-1];
    return fibonacci[n];
}       


int main(){
    int id, counter;
    memset(fibonacci, -1, sizeof(fibonacci));   
    fibonacci[0] = 1;
    fibonacci[1] = 1;

    cin >> id;
    for( counter = 0 ; counter < id ; counter++){
        cout << fib(counter-1, fibonacci);
        if(counter+1 != id) cout << " ";
    } cout << endl;

}
