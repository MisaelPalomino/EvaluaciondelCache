#!/bin/bash
cd "$(dirname "$0")/.."

make clean
make

mkdir -p resultados

./analisis todo | tee resultados/salida_completa.txt

valgrind --tool=cachegrind --cache-sim=yes \
    --cachegrind-out-file=resultados/cache_clasica.out \
    ./analisis clasica

valgrind --tool=cachegrind --cache-sim=yes \
    --cachegrind-out-file=resultados/cache_bloques.out \
    ./analisis bloques

cg_annotate resultados/cache_clasica.out > resultados/resumencache_clasica.txt
cg_annotate resultados/cache_bloques.out > resultados/resumencache_bloques.txt

kcachegrind resultados/cache_clasica.out &
kcachegrind resultados/cache_bloques.out &