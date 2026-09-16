#include "matriz.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

Matrix Bloques(const Matrix &A, const Matrix &B, int BS) {
    int n = A.size();
    Matrix C = crearMatrizCero(n);

    for (int ii = 0; ii < n; ii += BS) {
        for (int jj = 0; jj < n; jj += BS) {
            for (int kk = 0; kk < n; kk += BS) {
                for (int i = ii; i < min(ii + BS, n); i++) {
                    for (int j = jj; j < min(jj + BS, n); j++) {
                        double sum = 0.0;
                        for (int k = kk; k < min(kk + BS, n); k++) {
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] += sum;
                    }
                }
            }
        }
    }
    return C;
}

Matrix BloquesIkj(const Matrix &A, const Matrix &B, int BS) {
    int n = A.size();
    Matrix C = crearMatrizCero(n);

    for (int ii = 0; ii < n; ii += BS) {
        for (int kk = 0; kk < n; kk += BS) {
            for (int jj = 0; jj < n; jj += BS) {
                for (int i = ii; i < min(ii + BS, n); i++) {
                    for (int k = kk; k < min(kk + BS, n); k++) {
                        double aik = A[i][k];
                        for (int j = jj; j < min(jj + BS, n); j++) {
                            C[i][j] += aik * B[k][j];
                        }
                    }
                }
            }
        }
    }
    return C;
}

void analizarBloques() {
    cout << " MULTIPLICACION DE MATRICES POR BLOQUES";

    vector<int> tamanos = {256, 512, 1024};
    vector<int> bloques = {16, 32, 64, 128, 256};

    for (int n : tamanos) {
        Matrix A = crearMatriz(n);
        Matrix B = crearMatriz(n);

        cout << "\n--- n = " << n << " ---\n";
        cout << left << setw(8) << "BS"
             << setw(18) << "Clasica (ms)"
             << setw(18) << "Bloques ijk (ms)"
             << setw(18) << "Bloques ikj (ms)"
             << setw(12) << "Mejor" << "\n";
        cout << string(74, '-') << "\n";

        double t0 = tiempo0();
        Matrix Cref = Clasica(A, B);
        double t1 = tiempo0();
        double tClasica = t1 - t0;

        double mejor = tClasica;
        int mejorBS = 0;
        string mejorTipo = "clasica";

        for (int bs : bloques) {
            if (bs > n) continue;

            double ta = tiempo0();
            Matrix C1 = Bloques(A, B, bs);
            double tb = tiempo0();

            double tc = tiempo0();
            Matrix C2 = BloquesIkj(A, B, bs);
            double td = tiempo0();

            double t1ms = tb - ta;
            double t2ms = td - tc;

            string ganador = "clasica";
            double tMin = tClasica;
            if (t1ms < tMin) { tMin = t1ms; ganador = "bloques-ijk"; }
            if (t2ms < tMin) { tMin = t2ms; ganador = "bloques-ikj"; }
            if (tMin < mejor) { mejor = tMin; mejorBS = bs; mejorTipo = ganador; }

            cout << left << setw(8) << bs
                 << setw(18) << fixed << setprecision(3) << tClasica
                 << setw(18) << t1ms
                 << setw(18) << t2ms
                 << setw(12) << ganador << "\n";

            volatile double chk = C1[0][0] + C2[0][0];
            (void)chk;
        }
        cout << string(74, '-') << "\n";
        cout << "Mejor: " << mejorTipo << " con BS=" << mejorBS
             << " (" << fixed << setprecision(3) << mejor << " ms)\n";
    }
}