#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <utility>
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
void torna_matriz_dominante(int n, vector<vector<double>> &A, vector<double> &b) {
    double maior;
    int imaior;
    for (int i = 0; i < n; ++i) {
        maior = fabs(A[i][i]);
        imaior = i;
        for (int j = 0; j < n; ++j) {
            if (i != j && fabs(A[i][j]) > maior) {
                maior = fabs(A[j][i]);
                imaior = j;
            }
        }
        if (imaior != i)
            swap(A[i], A[imaior]);
            swap(b[i], b[imaior]);
    }
}
