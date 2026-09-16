#include "matriz.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

long long Ver1Filas(const Matrix &A,
                    const vector<double> &x,
                    vector<double> &y)
{
    long long contador = 0;
    int n = A.size();
    for (int i = 0; i < n; i++)
    {
        double sum = 0.0;
        for (int j = 0; j < n; j++)
        {
            sum += A[i][j] * x[j];
            contador++;
        }
        y[i] = sum;
    }
    return contador;
}

long long Ver2Columnas(const Matrix &A,
                       const vector<double> &x,
                       vector<double> &y)
{
    long long contador = 0;
    int n = A.size();
    for (int i = 0; i < n; i++)
        y[i] = 0.0;
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            y[i] += A[i][j] * x[j];
            contador++;
        }
    }
    return contador;
}

void analizarBuclesPacheco()
{
    cout << " 1. Bucles Pacheco\n";

    vector<int> tamanos = {256, 512, 1024, 2048, 4096};
    const int makumba = 10;

    cout << left << setw(10) << "n"
         << setw(18) << "Iteraciones"
         << setw(22) << "Filas prom (ms)"
         << setw(22) << "Columnas prom (ms)" << "\n";
         cout << string(84, '-') << "\n";

    for (int n : tamanos)
    {
        Matrix A = crearMatriz(n);

        vector<double> x(n);
        for (int i = 0; i < n; i++)
            x[i] = 1.0 + (i % 10);

        vector<double> y1(n, 0.0), y2(n, 0.0);

        double sumaFilas = 0.0;
        double sumaColumnas = 0.0;
        long long iteraciones = 0;

        for (int r = 0; r < makumba; r++)
        {
            double t1 = tiempo0();
            iteraciones = Ver1Filas(A, x, y1);
            double t2 = tiempo0();
            sumaFilas += (t2 - t1);

            double t3 = tiempo0();
            Ver2Columnas(A, x, y2);
            double t4 = tiempo0();
            sumaColumnas += (t4 - t3);
        }

        double promFilas = sumaFilas / makumba;
        double promColumnas = sumaColumnas / makumba;

        cout << left << setw(10) << n
             << setw(18) << iteraciones
             << setw(22) << fixed << setprecision(3) << promFilas
             << setw(22) << promColumnas << "\n";
    }
}