#include <iostream>
#include <tuple>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

tuple<string, string> pegar_matrizes(int dimensao){
    if(dimensao == 4){
        return tuple<string,string>{"..\\matrizes\\A4x4.txt","..\\matrizes\\B4x4.txt"};
    }else if(dimensao == 8)
        return tuple<string,string>{"..\\matrizes\\A8x8.txt","..\\matrizes\\B8x8.txt"};
    else if(dimensao == 16)
        return tuple<string,string>{"..\\matrizes\\A16x16.txt","..\\matrizes\\B16x16.txt"};
    else if(dimensao == 32)
        return tuple<string,string>{"..\\matrizes\\A32x32.txt","..\\matrizes\\B32x32.txt"};
    else if(dimensao == 64)
        return tuple<string,string>{"..\\matrizes\\A64x64.txt","..\\matrizes\\B64x64.txt"};
    else if(dimensao == 128)
        return tuple<string,string>{"..\\matrizes\\A128x128.txt","..\\matrizes\\B128x128.txt"};
    else if(dimensao == 256)
        return tuple<string,string>{"..\\matrizes\\A256x256.txt","..\\matrizes\\B256x256.txt"};
    else if(dimensao == 512)
        return tuple<string,string>{"..\\matrizes\\A512x512.txt","..\\matrizes\\B512x512.txt"};
    else if(dimensao == 1024)
        return tuple<string,string>{"..\\matrizes\\A1024x1024.txt","..\\matrizes\\B1024x1024.txt"};
    else if(dimensao == 2048)
        return tuple<string,string>{"..\\matrizes\\A2048x2048.txt","..\\matrizes\\B2048x2048.txt"};
    else
        return tuple<string,string>{"",""};

}

vector<vector<int>> arquivo_para_matriz(string f){
    ifstream file(f);
    vector<int> lines;
    
    vector<vector<int>> matriz;
    string line;
    string value;

    while(getline(file, line)){
        for (size_t i = 0; i < line.size(); i++)
        {   
            value += line[i];
            if(line[i] == ' ' || i == line.size() - 1){
                lines.push_back(stoi(value));
                value = "";
            }
            
        }
        value = "";
        matriz.push_back(lines);
        lines.clear();
    }

    return matriz;
}

char* nome_arquivo_resultado(int dimensao){
    if(dimensao == 4)
        return "..\\matrizes_resultado\\C4x4.txt";
    else if(dimensao == 8)
        return "..\\matrizes_resultado\\C8x8.txt";
    else if(dimensao == 16)
        return "..\\matrizes_resultado\\C16x16.txt";
    else if(dimensao == 32)
        return "..\\matrizes_resultado\\C32x32.txt";
    else if(dimensao == 64)
        return "..\\matrizes_resultado\\C64x64.txt";
    else if(dimensao == 128)
        return "..\\matrizes_resultado\\C128x128.txt";
    else if(dimensao == 256)
        return "..\\matrizes_resultado\\C256x256.txt";
    else if(dimensao == 512)
        return "..\\matrizes_resultado\\C512x512.txt";
    else if(dimensao == 1024)
        return "..\\matrizes_resultado\\C1024x1024.txt";
    else if(dimensao == 2048)
        return "..\\matrizes_resultado\\C2048x2048.txt";
    else
        return "";
    
}

bool criar_resultado_txt(int dimensao, vector<vector<int>> matriz){
    ofstream arq(nome_arquivo_resultado(dimensao)); // criando arquivo para matriz resultado

    if (!arq.good()){ // Se nào conseguiu criar
        cout << "Problemas na CRIACAO do arquivo" << endl;
        return false;
    }

    // anexando valores no arquivo texto
    for (size_t i = 0; i < matriz.size(); i++){
        for (size_t j = 0; j < matriz[i].size(); j++){
            arq << matriz[i][j] << "\t";
        }
        arq << endl;
    }
    arq.close();
    return true;
}

/* 
 * Pegar o maior valor dos tempos
 *
*/
double maior_tempo(vector<chrono::duration<double>> durations){
    
    double maior = durations[0].count();
    for (size_t i = 0; i < durations.size(); i++){
        if(maior < durations[i].count())
            maior = durations[i].count();
    }
    
    return maior;
}

/* 
 * Pegar o menor valor dos tempos
 *
*/
double menor_tempo(vector<chrono::duration<double>> durations){
    
    double menor = durations[0].count();
    for (size_t i = 0; i < durations.size(); i++){
        if(menor > durations[i].count())
            menor = durations[i].count();
    }
    
    return menor;
}

/* 
 * Calcular a media dos tempos
 *
*/
double media_tempo(vector<chrono::duration<double>> durations){
    
    double media = 0;
    for (size_t i = 0; i < durations.size(); i++){
        media +=durations[i].count();
    }
    
    media = media / durations.size();
    return media;
}

/* 
 * Calcular o desvio padrao dos tempos
 *
*/
double desvio_padrao_tempo(vector<chrono::duration<double>> durations){
    
    double media = media_tempo(durations);
    double desvio_padrao = 0;
    for (size_t i = 0; i < durations.size(); i++){
        desvio_padrao += pow(2, (durations[i].count() - media));
    }

    desvio_padrao = sqrt(desvio_padrao / 20);
    
    return desvio_padrao;
}


/* 
 * Registrar todas as informacoes de tempo na pasta
 *
*/
bool registrar_tempos(int dimensao, vector<chrono::duration<double>> durations, char algoritmo){

    ifstream arq_tempo_ler;

    if(algoritmo == 'S')
        ifstream arq_tempo_ler("../tempos/sequencial.txt");
    else if (algoritmo == 'C')
        ifstream arq_tempo_ler("../tempos/concorrente.txt");
    else {
        cout << "tipo de algoritmo nao conhecido." << endl;
        return false;
    }
    string line;
    string arq_tempo_string; 
    while(getline(arq_tempo_ler, line)){
        arq_tempo_string += line + '\n';
    }
    arq_tempo_ler.close();

    ofstream arq_tempo("../tempos/sequencial.txt");
    arq_tempo << arq_tempo_string << dimensao << ":" << endl << "[";

    for (size_t i = 0; i < durations.size(); i++){
        arq_tempo << durations[i].count();
        if(i != durations.size() - 1)
            arq_tempo << " , ";
    }
    arq_tempo << " ] " << endl 
    << "| Maior: " << maior_tempo(durations) 
    << " | Menor: " << menor_tempo(durations)
    << " | Media: " << media_tempo(durations)
    << " | Desvio_Padrao: " << desvio_padrao_tempo(durations) << endl << endl;

    arq_tempo.close();
    return true;
}