#include <iostream>
#include <string>

using namespace std;

int main()
{
    string word, names[8] = 
    {"aguia","pomba","vaca","homem",
        "pulga", "lagarta", "sanguessuga", "minhoca"};
    int animal = 1; 

    cin >> word;
    animal *=2;
    if (word == "invertebrado" )
        animal++;

    cin >> word;
    animal *=2;

    if ( word == "mamifero" || word == "anelideo" )
        animal++;

    cin >> word;
    animal *= 2;
    
    if( animal/2 != 6 ){
        if( word == "onivoro" )
            animal++;
    }
    else
        if( word == "herbivoro" )
            animal++;
    
    cout << names[animal%8] << endl;

}
