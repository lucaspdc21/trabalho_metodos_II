#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include "gaussjacobi.hpp"
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


    //int n = 3; // tamanho da matriz, será um dado de entrada. 
    // Definição do sistema linear Ax = b
    /*vector<vector<double>> A = {
        {5., 3.,  1.},
        {5.,  6., 1.},
        {1., 6.,  7.}
    };*/

    //vector<double> b = {1., 2., 3.};  // Vetor de termos independentes
    vector<double> x0(n, 0.0);    // Chute inicial
    //double epsilon = 0.000006;            // Critério de parada (erro máximo permitido)
    // Calculo da matriz inversa:
    vector<vector<double>> Ainv(n, vector<double>(n, 0.0)); 
    for (int i = 0; i < n; i++){
        vector<double> coluna(n, 0.0);
        coluna[i] = 1;
        pair<int,map<int, vector<double>>> resultadoinv = gauss_jacobi(n, A, coluna, x0, epsilon); 
        int linha = 0;
        for (int j = 0; j < n; j++) {
            Ainv[j][i] = resultadoinv.second[resultadoinv.first][j];
        }
    }

    // Exibindo a matriz inversa
    cout << "\nMatriz Inversa A^-1:\n";
    imprimirMatriz(Ainv);

    // Chamando a função de Gauss-Jacobi
    pair<int,map<int, vector<double>>> resultado = gauss_jacobi(n, A, b, x0, epsilon);

    // Exibindo os resultados
    cout << "\nIterações do método de Gauss-Jacobi:\n";
    for (const auto &par : resultado.second) {
        cout << "Iteração " << par.first << ": ";
        imprimirVetor(par.second);
    }
    
    cout << "\nVetor de deslocamentos {d}:\n";
    imprimirVetor(resultado.second[resultado.first]);
    imprimirJSON(Ainv, resultado);
    


    return 0;
}
