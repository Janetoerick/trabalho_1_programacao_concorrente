#include "../include/complemento.h"

using namespace complemento;

/*
* A partir de uma dimensao, pegar os arquivos pre existentes na pasta 'matrizes'
* checar se os arquivos estao bem e retornar caminho para os 2 arquivos de matriz
*
*/
tuple<string, string> complemento::pegar_matrizes(string dimensao){
    
    // Pegando arquivos com dimensao especificada
    tuple<string, string> files;
    if(dimensao == "4"){
        files = {"../matrizes/A4x4.txt","../matrizes/B4x4.txt"};
    }else if(dimensao == "8")
        files = {"../matrizes/A8x8.txt","../matrizes/B8x8.txt"};
    else if(dimensao == "16")
        files = {"../matrizes/A16x16.txt","../matrizes/B16x16.txt"};
    else if(dimensao == "32")
        files = {"../matrizes/A32x32.txt","../matrizes/B32x32.txt"};
    else if(dimensao == "64")
        files = {"../matrizes/A64x64.txt","../matrizes/B64x64.txt"};
    else if(dimensao == "128")
        files = {"../matrizes/A128x128.txt","../matrizes/B128x128.txt"};
    else if(dimensao == "256")
        files = {"../matrizes/A256x256.txt","../matrizes/B256x256.txt"};
    else if(dimensao == "512")
        files = {"../matrizes/A512x512.txt","../matrizes/B512x512.txt"};
    else if(dimensao == "1024")
        files = {"../matrizes/A1024x1024.txt","../matrizes/B1024x1024.txt"};
    else if(dimensao == "2048")
        files = {"../matrizes/A2048x2048.txt","../matrizes/B2048x2048.txt"};
    else
        files = {"",""}; // Caso nao seja nenhum numero, atribuir "" aos 2 valores
    
    // abrindo arquivos
    ifstream file_a(get<0>(files));
    ifstream file_b(get<1>(files));

    // checando se a dimensao existe nas matrizes exemplo para o trabalho
    if(get<0>(files) == ""){
        cout << "ERROR: DIMENSOES NAO EXISTENTES NA BASE DE DADOS" << endl;
        return files;
    }

    // checando se os dois arquivos foram abertos
    if(!file_a.is_open()){
        cout << "ERROR: PROBLEMAS NA ABERTURA DO ARQUIVO 1" << endl;
        return {"", ""};
    } else if(!file_b.is_open()){
        cout << "ERROR: PROBLEMAS NA ABERTURA DO ARQUIVO 2" << endl;
        return {"", ""};
    }
    file_a.close(); // fechando arquivo a
    file_b.close(); // fechando arquivo b
    
    return files;
}

/*
* Consturindo e retornando matriz a partir do caminho de arquivo dado
*
*/
vector<vector<int>> complemento::arquivo_para_matriz(string f){

    ifstream file(f);       // abrindo arquivo
    vector<int> lines;      // variavel para pegar valores linha a linha da matriz
    
    vector<vector<int>> matriz; // matriz total
    string line;                // variavel para pegar linha a linha do arquivo de texto
    string value;               // variavel para pegar os valores individuais da linha do arquivo de texto

    // percorrendo as linhas do arquivo convertendo os valores individuais em inteiros na matriz 'matriz'
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
    file.close(); // fechando arquivo

    return matriz;
}

/*
* Criar arquivo resultado a partir de uma matriz obtida
*
*/
bool complemento::criar_resultado_txt(int dimensao, int **matriz){
    string nome_arquivo_resultado = "../matrizes_resultado/C" + to_string(dimensao) + 
                                    "x" + to_string(dimensao) + ".txt";
    ofstream arq(nome_arquivo_resultado); // criando arquivo para matriz resultado

    if (!arq.good()){ // Se nào conseguiu criar
        cout << "ERROR: PROBLEMAS NA CRIACAO DO ARQUIVO RESULTADO" << endl;
        return false;
    }

    // anexando valores no arquivo texto
    for (size_t i = 0; i < dimensao; i++){
        for (size_t j = 0; j < dimensao; j++){
            arq << matriz[i][j] << "\t";
        }
        arq << endl;
    }
    arq.close(); // fechando arquivo
    return true;
}

/* 
 * Registrar todas as informacoes de tempo na pasta 'tempos'
 *
*/
bool complemento::registrar_tempos(int dimensao, chrono::duration<double> duracao, char algoritmo){

    string file;
    if(algoritmo == 'S')
        file = "../tempos/sequencial/dimensao_"+ to_string(dimensao) +".txt";
    else if(algoritmo == 'C')
        file = "../tempos/concorrente/dimensao_"+ to_string(dimensao) +".txt";
    else{
        cout << "ERROR: TIPO DE ALGORITMO NAO REGISTRADO OBTER TEMPO DE EXECUCAO!" << endl;
        return false;
    }

    // abrindo arquivo para ler o que tem dentro
    ifstream arq_tempo_ler(file);

    // Salvar informacoes do arquivo
    string line;                // variavel para percorrer linha a linha do arquivo de texto
    string arq_tempo_string;    // variavel para salvar todo conteudo existente no arquivo
    while(getline(arq_tempo_ler, line)){
        arq_tempo_string += line + '\n';
    }
    arq_tempo_ler.close();

    // abrindo o arquivo para escrever
    ofstream arq_tempo(file);

    arq_tempo << arq_tempo_string << "Tempo de execução: " << duracao.count() << endl
    << "----------------------------------" << endl;

    arq_tempo.close(); // fechando arquivo
    return true;
}