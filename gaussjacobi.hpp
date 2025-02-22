#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <utility>
#include "padrao.hpp"
#define MAX_ITER 1000
using namespace std; 

// func recebe tamanho da matriz, a matriz A, o vetor d ( sistema Ax = d ), o chute inicial x0, o erro e o max de iterações
pair<int,map<int, vector<double>>> gauss_jacobi(int n, const vector<vector<double>> &A, 
    const vector<double> &d, vector<double> &x0, double epsilon) {
    //Construção do map que receberá cada valor de x 
    map<int, vector<double>> map_jacobi;
    map_jacobi.insert({0, x0}); 
    //Criando x1 nulo:
    vector<double> x1(n, 0.0);
    //Transformação de A em C ( Cx + g = x_k )
    //Lembrando que o formato é: xi = (1/aii)*(bi - ai1*x1_(k+1) - ai2*x2_(k+1) ... 0 - ai(i+1)*x(i+1)_k ... )
    vector<vector<double>> C(n, vector<double>(n, 0.0)); 
    vector<double> g(n, 0.0); 
    for (int i = 0; i < n; ++i) {
        double fator_linha = 1.0 / A[i][i];
        for (int j = 0; j < n; ++j) {
            if (i != j) { 
                C[i][j] = A[i][j] * fator_linha;
            }
    }
        g[i] = d[i] * fator_linha;
    }
    int k = 0;
    // Iterações de Jacobi
    while (true) {
    ++k;
    for (int i = 0; i < n; ++i) {
        double soma = 0.0;
        for (int j = 0; j < n; ++j) {
            if (i != j) {   
            soma += C[i][j]*x0[j];
            }
        }
        x1[i] = g[i] - soma;
        }
    map_jacobi.emplace(k, x1);
    double norma = calcula_norma_relativa(n, x0, x1);
    if (norma <= epsilon || k >= MAX_ITER )
        break; 
    x0 = x1; 
    }
    return pair(k,map_jacobi);
}