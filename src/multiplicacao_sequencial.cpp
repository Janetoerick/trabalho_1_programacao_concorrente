#include <vector>
#include <iostream>
#include <chrono>
#include <fstream>
#include "complemento.cpp"

using namespace std;

void multiplicador_matriz(string dimensao){
    // transformando dimensao em int
    int dimensao_int = stoi(dimensao);

    // pegar o caminho de arquivo das matrizes a e b de dimensao x
    tuple<string, string> files = pegar_matrizes(dimensao_int);

    // abrindo arquivos
    ifstream file_a(get<0>(files));
    ifstream file_b(get<1>(files));
    
    // checando se a dimensao existe nas matrizes exemplo para o trabalho
    if(get<0>(files) == ""){
        cout << "dimensoes nao existentes na base de dados, tente outra dimensao" << endl;
        return;
    }

    // checando se os dois arquivos foram abertos
    if(!file_a.is_open()){
        cout << "Problemas na abertura do arquivo 1" << endl;
        return;
    } else if(!file_b.is_open()){
        cout << "Problemas na abertura do arquivo 2" << endl;
        return;
    }

    //criando as matrizes a, b e c(matriz resultado de a x b) 
    vector<vector<int>> matriz_a = arquivo_para_matriz(get<0>(files));
    vector<vector<int>> matriz_b = arquivo_para_matriz(get<1>(files));
    vector<vector<int>> matriz_result;

    // verificando se as matrizes a e b sao compativeis para multiplicar
    if(matriz_a[0][1] != matriz_b[0][0]){
        cout << "Matrizes encompativeis para multiplicacao" << endl;
        return;
    }
    
    // criando variavel para registrar o tempo total de execucao do calculo
    chrono::duration<double> total(0);

    // criando variaveis de apoio para o calculo
    int soma;                   // resultado de cada elemento
    int count = 0;              // contador de iteracoes das multiplicacoes
    vector<int> line_result;    // linha de resultados para ser gravada na matriz resultado
    vector<chrono::duration<double>> durations; // registro de tempos nas 20 execucoes
    
    while(count < 20){
    auto inicio = chrono::steady_clock::now(); // Pegando tempo a partir desse ponto (largada)

        for (size_t i = 0; i < matriz_a[0][0]; i++)
        {
            for (size_t j = 0; j < matriz_b[0][1]; j++)
            {
                soma = 0;
                for (size_t k = 0; k < matriz_a[0][1]; k++)
                {   
                    soma = soma + (matriz_a[i+1][k] * matriz_b[k+1][j]);
                    //cout << "soma:" << soma << " += matriz_a[" << 
                    //i << "][" << k << "]:" << matriz_a[i+1][k] << 
                    //" * matriz_b[" << k << "][" << j << "]:" <<
                    //matriz_b[k+1][j] << endl;
                }
                line_result.push_back(soma);

            }
            matriz_result.push_back(line_result);
            line_result.clear();
        }

        auto fim = chrono::steady_clock::now(); // pegando o tempo do final da execucao
        total = fim - inicio; // Pegando o tempo de execucao da funcao
        durations.push_back(total); // gravando resultado
        count++; // partindo para outra execucao

        if(count < 20) // Pegando a matriz apenas 1 vez
            matriz_result.clear();
        
    }
    file_a.close();
    file_b.close();
    // criando arquivo da matriz resultado em "..\matrizes_resultado\sequencial"
    if(!criar_resultado_txt(dimensao_int, matriz_result))
        return;

    if(registrar_tempos(dimensao_int, durations))
        return;
    
}

void print_matriz(vector<vector<int>> m){
    for (size_t i = 1; i < m.size(); i++)
    {
        for (size_t j = 0; j < m[i].size(); j++)
        {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}