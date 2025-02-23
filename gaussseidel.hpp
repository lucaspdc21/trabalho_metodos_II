pair<int, map<int, vector<double>>> gauss_seidel(int n, const vector<vector<double>> &A, 
    const vector<double> &d, vector<double> &x0, double epsilon) {
    // Construção do map que armazenará os valores de x por iteração
    map<int, vector<double>> map_seidel;
    map_seidel.insert({0, x0}); 
    int k = 0;
    while (true) {
        ++k;
        for (int i = 0; i < n; ++i) {
            double soma = d[i];
            for (int j = 0; j < n; ++j) {
                if (i != j) {   
                    soma -= A[i][j] * x0[j];
                }
            }
            x0[i] = soma / A[i][i];
        }
        map_seidel.emplace(k, x0);
        double norma = calcula_norma_relativa(n, map_seidel[k - 1], x0);
        if (norma <= epsilon || k >= MAX_ITER)
            break; 
    }
    return {k, map_seidel};
}