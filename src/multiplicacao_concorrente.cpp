#include <vector>
#include <iostream>
#include <chrono>
#include <fstream>
#include <thread>
#include "complemento.cpp"

using namespace std;

int **matriz_result; // resultado da multiplicacao

/*
* Método usado pelas threds para calcular uma linha da matriz e depositar os resultados
* na variavel global 'matriz_result'
* 
*/
void multiplicar_linha(vector<vector<int>> m_a, vector<vector<int>> m_b, int linha){
    int soma;  // variavel para calcular o valor de cada elemento
    for (size_t i = 0; i < m_b[0][1]; i++) {
        soma = 0;
        for (size_t j = 0; j < m_a[0][1]; j++) {
            soma = soma + (m_a[linha+1][j] * m_b[j+1][i]);
        }
        matriz_result[linha][i] = soma;
    }
}


void multiplicador_matriz_c(string dimensao){

    // pegar o caminho de arquivo das matrizes a e b de dimensao x
    tuple<string, string> files = pegar_matrizes(dimensao);

    if(get<0>(files) == "")
        return;

    // transformando dimensao em int
    int dimensao_int = stoi(dimensao);

    // //criando as matrizes a, b e preenchendo com os valores dos arquivos txt
    vector<vector<int>> matriz_a = arquivo_para_matriz(get<0>(files));
    vector<vector<int>> matriz_b = arquivo_para_matriz(get<1>(files));

    // // verificando se as matrizes a e b sao compativeis para multiplicar
    if(matriz_a[0][1] != matriz_b[0][0]){
        cout << "Matrizes encompativeis para multiplicacao" << endl;
        return;
    }

    matriz_result = new int *[dimensao_int];
    for (size_t i = 0; i < dimensao_int; i++) {
        matriz_result[i] = new int[dimensao_int];
    }

    // // criando variaveis de apoio para o calculo
    int soma;                   // resultado de cada elemento

    thread threads[dimensao_int];
    auto inicio = chrono::steady_clock::now(); // Pegando tempo a partir desse ponto (largada)

    for (size_t i = 0; i < dimensao_int; i++){
        threads[i] = thread (multiplicar_linha, matriz_a, matriz_b, i);
    }

    for (size_t i = 0; i < dimensao_int; i++) {
        threads[i].join();
    }   

    auto fim = chrono::steady_clock::now(); // pegando o tempo do final da execucao
    std::chrono::duration<double, milli> total = fim - inicio; // Pegando o tempo de execucao da funcao em milisegundos
    //auto total = chrono::duration_cast<chrono::seconds>(fim - inicio); // pegando o tempo de execucao da funcao em segundos

    // // criando arquivo da matriz resultado em "..\matrizes_resultado"
    if(!criar_resultado_txt(dimensao_int, matriz_result))
        return;

    // // registrando tempos em "..\tempos\sequencial"
    if(registrar_tempos(dimensao_int, total, 'C'))
        return;
    
}