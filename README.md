# Evaluación del Cache

## Compilación y ejecución

### Compilar

```bash
make
```

### Ejecutar

```bash
./analisis <modo>
```

| Modo | Descripción |
|---|---|
| `todo` | Ejecuta todos los análisis. |
| `clasica` | Multiplicación clásica. |
| `bloques` | Multiplicación por bloques. |
| `bucles` | Comparación de bucles (row-major vs column-major). |

Ejemplo:

```bash
./analisis todo
```

O directamente con `make`:

```bash
make run
```

### Limpiar

```bash
make clean
```

---

## Script de evaluación con Valgrind

```bash
chmod +x scripts/evaluar.sh
./scripts/evaluar.sh
```

El script compila, ejecuta los análisis, corre Callgrind y Cachegrind sobre
`clasica` y `bloques`, genera los resúmenes en `resultados/` y abre
KCachegrind con los archivos de Cachegrind.
