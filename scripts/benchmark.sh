#!/bin/bash
cd "$(dirname "$0")/.."

make clean
make

mkdir -p resultados

./analisis todo | tee resultados/salida_completa.txt

valgrind --tool=callgrind --dump-instr=yes --collect-jumps=yes \
    --callgrind-out-file=resultados/cg_clasica.out \
    ./analisis clasica

valgrind --tool=callgrind --dump-instr=yes --collect-jumps=yes \
    --callgrind-out-file=resultados/cg_bloques.out \
    ./analisis bloques

echo ""
echo "=== Resumen Clasica ==="
callgrind_annotate resultados/cg_clasica.out | head -30

echo ""
echo "=== Resumen Bloques ==="
callgrind_annotate resultados/cg_bloques.out | head -30