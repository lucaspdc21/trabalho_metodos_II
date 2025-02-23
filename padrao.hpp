#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <utility>
#include <algorithms>
#define MAX_ITER 1000
using namespace std; 

double calcula_norma_relativa(int n, vector<double> &x0, vector<double> &x1) {
    double normaNumerador = 0.0;
    double normaDenominador = 0.0;  
  
    for (int i = 0; i < n; ++i) {
      double t = abs(x1[i] - x0[i]);
      if (t > normaNumerador)
        normaNumerador = t;
      if (abs(x1[i]) > normaDenominador)
        normaDenominador = abs(x1[i]);
    }
    // return com um if embutido: Se o denomimnador for zero, retorne zero, se não, retorne a divisão. 
    return (normaDenominador == 0.0) ? 0.0 : (normaNumerador / normaDenominador);
  }
bool matriz_diagonalmente_dominante(int n, const vector<vector<double>> &A) {
  for (int i = 0; i < n; ++i) {
      double soma = 0.0;
      for (int j = 0; j < n; ++j) {
          if (i != j) soma += abs(A[i][j]);
      }
      if (abs(A[i][i]) <= soma) return false;
  }
  return true;
}
bool tornar_diagonalmente_dominante(int n, vector<vector<double>> &A) {
  //Cria e inicializa um vetor que contém os índices de cada linha de A.
  //Será usado para criar permutações de linhas e reorganizar a matriz, 
  //Tentando torna-la dominante. 
  //Ele começa, é claro, em ordem natural, {0, 1, 2, 3...}, 
  //E depois será alterado pelo next_permutation. 
  vector<int> indices(n);
  for (int i = 0; i < n; ++i) indices[i] = i;
  //Testando permutação:
  do {
      vector<vector<double>> B(n, vector<double>(n));
      for (int i = 0; i < n; ++i) {
        //Criando a matriz B que tem as linhas da Coluna A ordenadas em uma permutação aleatória 
          B[i] = A[indices[i]]; 
      }
      if (matriz_diagonalmente_dominante(n, B)) {
        //Se temos uma matriz que converge, retornamos
          A = B;
          return true;
      }
      //next permutation fornece uma permutação nova do vetor indices até não houverem mais permutações. 
  } while (next_permutation(indices.begin(), indices.end()));
  
  return false;
}
