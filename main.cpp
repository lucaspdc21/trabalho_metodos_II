#include "gaussjacobi.hpp"
using namespace std;

int main() {
    // Definição do sistema linear Ax = d
    vector<vector<double>> A = {
        {4, -1,  0},
        {-1,  4, -1},
        {0, -1,  3}
    };

    vector<double> d = {15, 10, 10};  // Vetor de termos independentes
    vector<double> x0 = {0, 0, 0};    // Chute inicial
    double epsilon = 0.000006;            // Critério de parada (erro máximo permitido)

    // Chamando a função de Gauss-Jacobi
    map<int, vector<double>> resultado = gauss_jacobi(3, A, d, x0, epsilon);

    // Exibindo os resultados
    cout << "Iterações do método de Gauss-Jacobi:\n";
    for (const auto &par : resultado) {
        cout << "Iteração " << par.first << ": ";
        for (double val : par.second) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
