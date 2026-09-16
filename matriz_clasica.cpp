#include "matriz.h"
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace std::chrono;

Matrix Clasica(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C = crearMatrizCero(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < n; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    return C;
}

void analizarClasica() {
 

    vector<int> tamanos = {64, 128, 256, 512, 1024};

    cout << left << setw(10) << "n"
         << setw(15) << "Iteraciones"
         << setw(20) << "Tiempo (ms)"
         << setw(20) << "ms / n^3" << "\n";
    cout << string(65, '-') << "\n";

    for (int n : tamanos) {
        Matrix A = crearMatriz(n);
        Matrix B = crearMatriz(n);

        double t1 = tiempo0();
        Matrix C = Clasica(A, B);
        double t2 = tiempo0();

        double ms = t2 - t1;
        long long iter = (long long)n * n * n;

        cout << left << setw(10) << n
             << setw(15) << iter
             << setw(20) << fixed << setprecision(3) << ms
             << setw(20) << scientific << setprecision(3)
             << (ms / (double)iter) << "\n";

        volatile double chk = C[0][0];
        (void)chk;
    }


}