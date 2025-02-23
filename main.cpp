#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include "gaussjacobi.hpp"
#include "gaussseidel.hpp"
#include <fstream>

using namespace std;

void imprimirJSON(const vector<vector<double>> &Ainv, const pair<int, map<int, vector<double>>> &resultado) {
    ofstream arquivo("backend/resultado.json");
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo JSON para escrita.\n";
        return;
    }

    // Início do JSON
    arquivo << "{\n";

    // Matriz Inversa (Ainv)
    arquivo << "  \"Ainv\": [\n";
    for (size_t i = 0; i < Ainv.size(); ++i) {
        arquivo << "    [";
        for (size_t j = 0; j < Ainv[i].size(); ++j) {
            arquivo << Ainv[i][j];
            if (j < Ainv[i].size() - 1) arquivo << ", ";
        }
        arquivo << "]"; 
        if (i < Ainv.size() - 1) arquivo << ",";
        arquivo << "\n";
    }
    arquivo << "  ],\n";

    // Iterações
    arquivo << "  \"iteracoes\": [\n";
    bool firstIter = true;
    for (const auto &par : resultado.second) {
        if (!firstIter) arquivo << ",\n";
        firstIter = false;
        
        arquivo << "    {\n";
        arquivo << "      \"iteracao\": " << par.first << ",\n";
        arquivo << "      \"valores\": [";
        for (size_t i = 0; i < par.second.size(); ++i) {
            arquivo << par.second[i];
            if (i < par.second.size() - 1) arquivo << ", ";
        }
        arquivo << "]\n";
        arquivo << "    }";
    }
    arquivo << "\n  ],\n";

    // Vetor de deslocamentos
    arquivo << "  \"deslocamentos\": [";
    const vector<double>& deslocamentos = resultado.second.at(resultado.first);
    for (size_t i = 0; i < deslocamentos.size(); ++i) {
        arquivo << deslocamentos[i];
        if (i < deslocamentos.size() - 1) arquivo << ", ";
    }
    arquivo << "]\n";

    // Fechamento do JSON
    arquivo << "}\n";

    arquivo.close();
    cout << "\nArquivo 'resultado.json' salvo com sucesso.\n";
}


void receber_entrada(int &n, vector<vector<double>> &A, vector<double> &b, double &epsilon){
    cout << "Digite a quantidade de deslocamentos(d1,d2,...,dn): ";
    cin >> n;
    
    // Redefinindo o tamanho dos vetores
    A.resize(n, vector<double>(n));
    b.resize(n);
    
    cout << "Digite todos os elementos da matriz A:'\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "A[" << i+1 << "][" << j+1 << "]: ";
            cin >> A[i][j];
        }
    }

    cout << "Digite os elementos do vetor b:\n";
    for (int i = 0; i < n; i++) {
        cout << "b[" << i+1 << "]: ";
        cin >> b[i];
    }

    cout << "Digite a precisão desejada: ";
    cin >> epsilon;
}

void imprimirMatriz(const vector<vector<double>> &matriz) {
    cout << fixed << setprecision(1);
    for (const auto &linha : matriz) {
        cout << "[ ";
        for (double val : linha) {
            cout << val << " ";
        }
        cout << "]\n";
    }
}

void imprimirVetor(const vector<double> &vetor) {
    cout << fixed << setprecision(6);
    for (double val : vetor) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    // Definição das variáveis preenchidas pelo usuário
    int n;
    vector<vector<double>> A;
    vector<double> b;
    double epsilon;

    // Recebendo a entrada do usuário
    receber_entrada(n, A, b, epsilon);
    cout << "Gostaria de checar o critério de convergência de linhas? 0 para não, 1 para sim." << "\n";
    int check; 
    cin >> check; 
    if (check == 1){
        cout << "Checando critério de convergência por linhas..." << "\n";
        if (!matriz_diagonalmente_dominante(n, A)){
            if (!tornar_diagonalmente_dominante(n, A)){
            cout << "Essa matriz não tem garantia de convergência mesmo após tentativas de permutação das linhas" << "\n";
            cout << "Gostaria de tentar rodar mesmo assim? 0 para não, 1 para sim";
            int i;
            cin >> i; 
            if (i == 0){
                return NULL;
            }
        }
          cout << "Essa matriz não possuia garantia de convergência" << "\n";
          cout << "No entanto, após uma permutação das linhas, obtivemos uma matriz que tem garantia de convergência" << "\n";
          //TO-DO: Imprimir essa matriz nova, não sei como vão querer mostrar para o usuário
        }
        else{
            cout << "Essa matriz possui garantia de convergência";
        }
    }
    vector<double> x0(n);
    for (int i = 0; i < n; ++i) // Chute inicial
        x0[i] = b[i] / A[i][i];
    imprimirVetor(x0);
    // Calculo da matriz inversa:
    //Jacobi:
    vector<vector<double>> AinvJacobi(n, vector<double>(n, 0.0)); 
    for (int i = 0; i < n; i++){
        vector<double> colunaJacobi(n, 0.0);
        colunaJacobi[i] = 1;
        pair<int,map<int, vector<double>>> resultadoinvJacobi = gauss_jacobi(n, A, colunaJacobi, x0, epsilon); 
        for (int j = 0; j < n; j++) {
            AinvJacobi[j][i] = resultadoinvJacobi.second[resultadoinvJacobi.first][j];
        }
    }
    //Seidel:
    vector<vector<double>> AinvSeidel(n, vector<double>(n, 0.0)); 
    for (int i = 0; i < n; i++){
        vector<double> colunaSeidel(n, 0.0);
        colunaSeidel[i] = 1;
        pair<int,map<int, vector<double>>> resultadoinvSeidel = gauss_seidel(n, A, colunaSeidel, x0, epsilon); 
        for (int j = 0; j < n; j++){
            AinvSeidel[j][i] = resultadoinvSeidel.second[resultadoinvSeidel.first][j];
            }   
        }

    // Exibindo a matriz inversa
    cout << "\nMatriz Inversa A^-1:\n";
    cout << "\nGauss-Jacobi: A^-1:\n";
    imprimirMatriz(AinvJacobi);
    cout << "\nGauss-Seidel: A^-1:\n";
    imprimirMatriz(AinvSeidel); 

    // Chamando a função de Gauss-Jacobi
    pair<int,map<int, vector<double>>> resultadoJacobi = gauss_jacobi(n, A, b, x0, epsilon);
    // Chamando a função de Gauss-Seidel
    pair<int,map<int, vector<double>>> resultadoSeidel = gauss_seidel(n, A, b, x0, epsilon);
    // Exibindo os resultados
    cout << "\nIterações do método de Gauss-Jacobi:\n";
    for (const auto &par : resultadoJacobi.second) {
        cout << "Iteração " << par.first << ": ";
        imprimirVetor(par.second);
    }
    cout << "\nIterações do método de Gauss-Seidel:\n";
    for (const auto &par : resultadoSeidel.second) {
        cout << "Iteração " << par.first << ": ";
        imprimirVetor(par.second);
    }
    
    cout << "\nVetor de deslocamentos {d}:\n";
    imprimirVetor(resultadoJacobi.second[resultadoJacobi.first]);
    imprimirJSON(AinvJacobi, resultadoJacobi);
    imprimirVetor(resultadoSeidel.second[resultadoSeidel.first]);
    imprimirJSON(AinvSeidel, resultadoSeidel);
    


    return 0;
}
