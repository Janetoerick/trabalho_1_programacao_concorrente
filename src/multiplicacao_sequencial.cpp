#include <vector>
#include <iostream>
#include <chrono>
#include <fstream>
#include "../include/complemento.h"

using namespace std;
using namespace complemento;

void multiplicador_matriz_s(string dimensao){

    // pegar o caminho de arquivo das matrizes a e b de dimensao x
    tuple<string, string> files = pegar_matrizes(dimensao);

    if(get<0>(files) == "")
        return;

    // transformando dimensao em int
    int dimensao_int = stoi(dimensao);

    //criando as matrizes a, b e preenchendo com os valores dos arquivos txt
    vector<vector<int>> matriz_a = arquivo_para_matriz(get<0>(files));
    vector<vector<int>> matriz_b = arquivo_para_matriz(get<1>(files));

    // criando matriz para copular os valores resultado
    int **matriz_result;
    matriz_result = new int *[dimensao_int]; // criando a quantidade de linhas = dimensao passada
    for (size_t i = 0; i < dimensao_int; i++) { // criando a quantidade de colunas = dimensao passada
        matriz_result[i] = new int[dimensao_int]; 
    }

    // criando variaveis de apoio para o calculo
    int soma; // resultado de cada elemento
    
    auto inicio = chrono::steady_clock::now(); // Pegando tempo a partir desse ponto (largada)

    // multiplicando as matrizes
    for (size_t i = 0; i < matriz_a[0][0]; i++){
        for (size_t j = 0; j < matriz_b[0][1]; j++){
            soma = 0;
            for (size_t k = 0; k < matriz_a[0][1]; k++){   
                soma = soma + (matriz_a[i+1][k] * matriz_b[k+1][j]);
            }
            matriz_result[i][j] = soma;
        }
    }

    auto fim = chrono::steady_clock::now(); // pegando o tempo do final da execucao
    std::chrono::duration<double, milli> total = fim - inicio; // Pegando o tempo de execucao da funcao em milisegundos
    //auto total = chrono::duration_cast<chrono::seconds>(fim - inicio); // pegando o tempo de execucao da funcao em segundos
    

    // criando arquivo da matriz resultado em "..\matrizes_resultado"
    if(!criar_resultado_txt(dimensao_int, matriz_result))
        return;

    // registrando tempos em "..\tempos\sequencial"
    if(registrar_tempos(dimensao_int, total, 'S'))
        return;
    
}