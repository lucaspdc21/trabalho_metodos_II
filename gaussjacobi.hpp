#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <utility>
#include "norma.hpp"
#define MAX_ITER 1000
using namespace std; 

// func recebe tamanho da matriz, a matriz A, o vetor d ( sistema Ax = d ), o chute inicial x0, o erro e o max de iterações
map<int, vector<double>> gauss_jacobi(int n, vector<vector<double>> &A, 
    vector<double> &d, vector<double> &x0, double epsilon) {
    //Construção do map que receberá cada valor de x 
    map<int, vector<double>> map_jacobi;
    map_jacobi.insert({0, d}); 
    //Criando x1 nulo:
    vector<double> x1(n, 0.0);
    //Transformação de A em C ( Cx + g = x_k )
    //Lembrando que o formato é: xi = (1/aii)*(bi - ai1*x1_(k+1) - ai2*x2_(k+1) ... 0 - ai(i+1)*x(i+1)_k ... )
    for (int i = 0; i < n; ++i) {
        double fator_linha = 1.0 / A[i][i];
        for (int j = 0; j < n; ++j) {
            if (i != j) { 
                A[i][j] *= fator_linha;
            }
    }
        d[i] *= fator_linha;
    }
    int k = 0;
    // Iterações de Jacobi
    while (true) {
    ++k;
    for (int i = 0; i < n; ++i) {
        double soma = 0.0;
        for (int j = 0; j < n; ++j) {
            if (i != j) {
            soma += A[i][j]*x0[j];
            }
        }
        x1[i] = d[i] - soma;
        }
    double norma = calcula_norma_relativa(n, x1, x0);
    //essa função também atualiza o vetor x0 para receber x1, já que iremos reusar x0. 
    map_jacobi.insert({k, x1});
    if (norma <= epsilon || k >= MAX_ITER )
        break; 
    }
    return map_jacobi;
}