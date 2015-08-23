#include <iostream>

using namespace std;

int main(){
    int numbers, current, soma, i, n;
    cin >> numbers;
    for( i = 0 ; i < numbers ; i++ ){
        cin >> current;
        soma = 0;
        for( n = 1 ; n < current ; n++ )
            if( current%n == 0 ) soma+= n;
        if( soma==current)
            cout << current << " eh perfeito\n";
        else
            cout << current << " nao eh perfeito\n";
    }
}
