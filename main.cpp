#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include "gaussjacobi.hpp"
#include "gaussseidel.hpp"
#include <fstream>

using namespace std;

void imprimirJSON(const vector<vector<double>> &AinvJacobi, const pair<int, map<int, vector<double>>> &resultadoJacobi,
    const vector<vector<double>> &AinvSeidel, const pair<int, map<int, vector<double>>> &resultadoSeidel) {
    // Gerar JSON para Gauss-Jacobi
    ofstream arquivoJacobi("backend/resultado_jacobi.json");
    if (!arquivoJacobi.is_open()) {
        cerr << "Erro ao abrir o arquivo JSON para escrita (Gauss-Jacobi).\n";
        return;
    }

    // Início do JSON para Gauss-Jacobi
    arquivoJacobi << "{\n";

    // Matriz Inversa (Ainv) para Gauss-Jacobi
    arquivoJacobi << "  \"Ainv\": [\n";
    for (size_t i = 0; i < AinvJacobi.size(); ++i) {
        arquivoJacobi << "    [";
        for (size_t j = 0; j < AinvJacobi[i].size(); ++j) {
            arquivoJacobi << AinvJacobi[i][j];
            if (j < AinvJacobi[i].size() - 1) arquivoJacobi << ", ";
        }
        arquivoJacobi << "]"; 
        if (i < AinvJacobi.size() - 1) arquivoJacobi << ",";
        arquivoJacobi << "\n";
    }
    arquivoJacobi << "  ],\n";

    // Iterações para Gauss-Jacobi
    arquivoJacobi << "  \"iteracoes\": [\n";
    bool firstIterJacobi = true;
    for (const auto &par : resultadoJacobi.second) {
        if (!firstIterJacobi) arquivoJacobi << ",\n";
        firstIterJacobi = false;

        arquivoJacobi << "    {\n";
        arquivoJacobi << "      \"iteracao\": " << par.first << ",\n";
        arquivoJacobi << "      \"valores\": [";
        for (size_t i = 0; i < par.second.size(); ++i) {
            arquivoJacobi << par.second[i];
            if (i < par.second.size() - 1) arquivoJacobi << ", ";
        }
        arquivoJacobi << "]\n";
        arquivoJacobi << "    }";
    }
    arquivoJacobi << "\n  ],\n";

    // Vetor de deslocamentos para Gauss-Jacobi
    arquivoJacobi << "  \"deslocamentos\": [";
    const vector<double>& deslocamentosJacobi = resultadoJacobi.second.at(resultadoJacobi.first);
    for (size_t i = 0; i < deslocamentosJacobi.size(); ++i) {
        arquivoJacobi << deslocamentosJacobi[i];
        if (i < deslocamentosJacobi.size() - 1) arquivoJacobi << ", ";
    }
    arquivoJacobi << "]\n";

    // Fechamento do JSON para Gauss-Jacobi
    arquivoJacobi << "}\n";

    arquivoJacobi.close();
    cout << "\nArquivo 'resultado_jacobi.json' salvo com sucesso.\n";

    // Gerar JSON para Gauss-Seidel
    ofstream arquivoSeidel("backend/resultado_seidel.json");
    if (!arquivoSeidel.is_open()) {
        cerr << "Erro ao abrir o arquivo JSON para escrita (Gauss-Seidel).\n";
        return;
    }

    // Início do JSON para Gauss-Seidel
    arquivoSeidel << "{\n";

    // Matriz Inversa (Ainv) para Gauss-Seidel
    arquivoSeidel << "  \"Ainv\": [\n";
    for (size_t i = 0; i < AinvSeidel.size(); ++i) {
        arquivoSeidel << "    [";
        for (size_t j = 0; j < AinvSeidel[i].size(); ++j) {
            arquivoSeidel << AinvSeidel[i][j];
            if (j < AinvSeidel[i].size() - 1) arquivoSeidel << ", ";
        }
        arquivoSeidel << "]"; 
        if (i < AinvSeidel.size() - 1) arquivoSeidel << ",";
        arquivoSeidel << "\n";
    }
    arquivoSeidel << "  ],\n";

    // Iterações para Gauss-Seidel
    arquivoSeidel << "  \"iteracoes\": [\n";
    bool firstIterSeidel = true;
    for (const auto &par : resultadoSeidel.second) {
        if (!firstIterSeidel) arquivoSeidel << ",\n";
        firstIterSeidel = false;

        arquivoSeidel << "    {\n";
        arquivoSeidel << "      \"iteracao\": " << par.first << ",\n";
        arquivoSeidel << "      \"valores\": [";
        for (size_t i = 0; i < par.second.size(); ++i) {
            arquivoSeidel << par.second[i];
            if (i < par.second.size() - 1) arquivoSeidel << ", ";
        }
        arquivoSeidel << "]\n";
        arquivoSeidel << "    }";
    }
    arquivoSeidel << "\n  ],\n";

    // Vetor de deslocamentos para Gauss-Seidel
    arquivoSeidel << "  \"deslocamentos\": [";
    const vector<double>& deslocamentosSeidel = resultadoSeidel.second.at(resultadoSeidel.first);
    for (size_t i = 0; i < deslocamentosSeidel.size(); ++i) {
        arquivoSeidel << deslocamentosSeidel[i];
        if (i < deslocamentosSeidel.size() - 1) arquivoSeidel << ", ";
    }
    arquivoSeidel << "]\n";

    // Fechamento do JSON para Gauss-Seidel
    arquivoSeidel << "}\n";

    arquivoSeidel.close();
    cout << "\nArquivo 'resultado_seidel.json' salvo com sucesso.\n";
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
pair<bool,int> check_explode (  vector<double> vec,
                                double parameter=0.4){
    bool check = false;
    int n_comp = 0;
    int iter = 0;
    for (double n : vec){
        if (abs(n)>parameter){
            check = true;
            n_comp++;
        }
        ++iter;
    }
    return {check,n_comp};
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
          imprimirMatriz(A); 
        }
        else{
            cout << "Essa matriz possui garantia de convergência";
        }
    }
    vector<double> x0(n);
    for (int i = 0; i < n; ++i) // Chute inicial
        x0[i] = b[i] / A[i][i];
    cout << "Chute inicial x0: ";
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
    cout << "\nMatriz Inversa:\n";
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
    cout << "Gauss-Jacobi: \n"; 
    int n_j = resultadoJacobi.first;
    imprimirVetor(resultadoJacobi.second[resultadoJacobi.first]);
    pair<bool,int> check_jacobi = check_explode(resultadoJacobi.second[n_j],0.4);
    if (check_jacobi.first){
        cout    << "Pelo método de Gauss-Jacobi, o vetor apresenta " 
                << check_jacobi.second << " componente(s) de deslocamento que pode(m) gerar sérios danos"
                << endl;
    }
    else{ 
        cout    << "Pelo método de Gauss-Jacobi, o vetor apresenta não apresenta nenhum deslocamento que gere danos sérios ou problemas gigantescos";
    }
    cout << "Gauss-Seidel: \n"; 
    int n_s = resultadoSeidel.first;
    pair<bool,int> check_seidel = check_explode(resultadoSeidel.second[n_s],0.4);
    imprimirVetor(resultadoSeidel.second[resultadoSeidel.first]);
    if (check_seidel.first){
        cout    << "Pelo método de Gauss-Seidel, o vetor apresenta " 
                << check_seidel.second << " componente(s) de deslocamento que pode(m) gerar sérios danos"
                << endl;
    }
    else{
        cout    << "Pelo método de Gauss-Seidel, o vetor apresenta não apresenta nenhum deslocamento que gere danos sérios ou problemas gigantescos";
    }
    imprimirJSON(AinvJacobi, resultadoJacobi ,AinvSeidel, resultadoSeidel);


    return 0;
}
