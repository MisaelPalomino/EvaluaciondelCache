#include "matriz.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

Matrix crearMatriz(int n) {
    Matrix M(n, vector<double>(n));
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(1.0, 10.0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            M[i][j] = dist(gen);
    return M;
}


Matrix crearMatrizCero(int n) {
    return Matrix(n, vector<double>(n, 0.0));
}


void imprimir(const Matrix &M, const string &nombre) {
    cout << nombre << " (" << M.size() << "x"
         << (M.empty() ? 0 : M[0].size()) << "):\n";
    int n = M.size();
    if (n > 10) {
        cout << "  [matriz demasiado grande, se omite impresion]\n";
        return;
    }
    cout << fixed << setprecision(4);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (int)M[i].size(); j++)
            cout << setw(10) << M[i][j] << " ";
        cout << "\n";
    }
}


bool comparar(const Matrix &A, const Matrix &B, double tol) {
    if (A.size() != B.size()) return false;
    if (A.empty()) return B.empty();
    if (A[0].size() != B[0].size()) return false;

    for (size_t i = 0; i < A.size(); i++)
        for (size_t j = 0; j < A[i].size(); j++)
            if (fabs(A[i][j] - B[i][j]) > tol) {
                cerr << "Diferencia en [" << i << "][" << j << "]: "
                     << A[i][j] << " vs " << B[i][j] << "\n";
                return false;
            }
    return true;
}


double tiempo0() {
    auto ahora = high_resolution_clock::now();
    return duration<double, milli>(ahora.time_since_epoch()).count();
}