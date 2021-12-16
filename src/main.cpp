/**
 * @file main.cpp
 * @author Janeto Erick
 * @brief Classe Main
*/

#include <iostream>
#include <string>
#include <cstring>
#include "multiplicacao_sequencial.cpp"
#include "multiplicacao_concorrente.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
    
    if (argc != 3){
        cout << "Entrada irregular!" << endl;
        return 0;
    }

    // char char_array[2];
    // strcpy(char_array, argv[2]);
    
    string entrada_algoritmo(argv[2]);

    if(entrada_algoritmo.compare("S") == 0){
        multiplicador_matriz_s(argv[1]);
    }else if(entrada_algoritmo.compare("C") == 0){
        multiplicador_matriz_c(argv[1]);
    } else {
        cout << "ERROR: TIPO DE ALGORITMO NAO CONHECIDO " << endl;
    }
    

    return 0;
}