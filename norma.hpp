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
  
      // Atualiza o vetor x0 com o vetor x1
      x0[i] = x1[i];
    }
  
    double norma = normaNumerador / normaDenominador;
    return norma;
  }