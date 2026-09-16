#ifndef MATRIZ_H
#define MATRIZ_H
#include <vector>
#include <string>
using Matrix = std::vector<std::vector<double>>;
Matrix crearMatriz(int n);
Matrix crearMatrizCero(int n);
void imprimir(const Matrix &M, const std::string &nombre);
bool comparar(const Matrix &A, const Matrix &B, double tol = 1e-9);
Matrix Clasica(const Matrix &A, const Matrix &B);
Matrix Bloques(const Matrix &A, const Matrix &B, int BS);
Matrix BloquesIkj(const Matrix &A, const Matrix &B, int BS);
double tiempo0();
#endif