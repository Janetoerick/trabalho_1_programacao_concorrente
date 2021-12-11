/**
 * @file main.cpp
 * @author Janeto Erick
 * @brief Classe Main
*/

#include <iostream>
#include <string>
#include <cstring>
#include "multiplicacao_sequencial.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
    if (argc != 3){
        cout << "Entrada irregular!" << endl;
        return 0;
    }

    char char_array[2];
    strcpy(char_array, argv[2]);
    
    if(char_array[1] == ' ' || char_array[1] == NULL){
        if(char_array[0] == 'S'){
            multiplicador_matriz(argv[1]);
        }
    }
    

    return 0;
}