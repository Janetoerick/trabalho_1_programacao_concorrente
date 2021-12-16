#ifndef _COMPLEMENTO_
#define _COMPLEMENTO_

#include <iostream>
#include <tuple>
#include <fstream>
#include <chrono>
#include <vector>
#include <cmath>
using namespace std;

namespace complemento{
    tuple<string, string> pegar_matrizes(string dimensao);
    vector<vector<int>> arquivo_para_matriz(string f);
    string nome_arquivo_resultado(int dimensao);
    bool criar_resultado_txt(int dimensao, int **matriz);
    double maior_tempo(vector<chrono::duration<double>> durations);
    double menor_tempo(vector<chrono::duration<double>> durations);
    double media_tempo(vector<chrono::duration<double>> durations);
    double desvio_padrao_tempo(vector<chrono::duration<double>> durations);
    bool registrar_tempos(int dimensao, vector<chrono::duration<double>> durations, char algoritmo);
}


#endif