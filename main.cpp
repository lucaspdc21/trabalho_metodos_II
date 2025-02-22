#include <iostream>
#include <vector>
#include <map>
#include "gaussjacobi.hpp"
using namespace std;

int main() {
    
    //TO-DO: Fazer uma função para receber a matriz A de entrada (recebe n, os valores de cada termo 
    //de A, os valores de b, e a precisao )    


    int n = 3; // tamanho da matriz, será um dado de entrada. 
    // Definição do sistema linear Ax = b
    vector<vector<double>> A = {
        {5., 3.,  1.},
        {5.,  6., 1.},
        {1., 6.,  7.}
    };

    vector<double> b = {1., 2., 3.};  // Vetor de termos independentes
    vector<double> x0 = {0., 0., 0.};    // Chute inicial
    double epsilon = 0.000006;            // Critério de parada (erro máximo permitido)
    // Calculo da matriz inversa:
    vector<vector<double>> Ainv(n, vector<double>(n, 0.0)); 
    for (int i = 0; i < n; i++){
        vector<double> coluna(n, 0.0);
        coluna[i] = 1;
        pair<int,map<int, vector<double>>> resultadoinv = gauss_jacobi(n, A, coluna, x0, epsilon); 
        int linha = 0;
        for (const auto value : resultadoinv.second[resultadoinv.first]){
            Ainv[i][linha] = value;
            linha++; 
            }   
        }
    
    // Chamando a função de Gauss-Jacobi
    pair<int,map<int, vector<double>>> resultado = gauss_jacobi(3, A, b, x0, epsilon);

    // Exibindo os resultados
    cout << "Iterações do método de Gauss-Jacobi:\n";
    for (const auto &value : resultado.second) {
        cout << "Iteração " <<  << ": ";
        for (double val : par.second) {
            cout << val << " ";
        }
        cout << endl;
    }
    // Calculo da matriz inversa: 
    


    return 0;
}
