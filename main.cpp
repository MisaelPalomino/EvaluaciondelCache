#include <iostream>
#include <string>

void analizarBuclesPacheco();
void analizarClasica();
void analizarBloques();

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Uso: " << argv[0]
                  << " [bucles|clasica|bloques|todo]\n";
        return 1;
    }

    std::string modo = argv[1];

    if (modo == "bucles")        analizarBuclesPacheco();
    else if (modo == "clasica")  analizarClasica();
    else if (modo == "bloques")  analizarBloques();
    else if (modo == "todo") {
        analizarBuclesPacheco();
        analizarClasica();
        analizarBloques();
    } else {
        std::cout << "Modo desconocido: " << modo << "\n";
        return 1;
    }
    return 0;
}