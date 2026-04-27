# tarea01_paralela
---
Matrix multiplication using naive/tiling/strassen approach. Followed by OpenMP parallelized implementation.


### CLI de Compilación y Benchmarking

Script para automatizar la compilación, perfilado de rendimiento y validación de los algoritmos de multiplicación de matrices. Realiza barridos paramétricos sobre dimensiones de matrices, tamaños de bloque y configuración de hilos en OpenMP.

#### Uso General

```bash
chmod +x run
./run <acción> [--max_N <exponente>]
```

#### Acciones Principales

* **`compile`**: Compila los archivos `.cpp` de `test_suite/` con la bandera `-O2` (añadiendo `-fopenmp` para la versión paralela) bajo el estándar C++23. Los ejecutables se depositan en el directorio `bin/`.
* **`test`**: Ejecuta los binarios secuenciales. Realiza un barrido para matrices de tamaño `N = 2^i` (desde `i=2` hasta `max_N`), iterando internamente sobre distintos tamaños de bloque o caso base. Ejecuta cada configuración 10 veces.
* **`parallel_test`**: Ejecuta los binarios paralelos. Realiza un barrido escalonando la cantidad de hilos (`OMP_NUM_THREADS`) y los tamaños de caso base para matrices.
* **`validate`**: Ejecuta el binario `./bin/alg_validation` utilizando la matriz de tamaño máximo para verificar de forma automatizada la correctitud matemática de todas las implementaciones.

#### Parámetros Opcionales

* **`--max_N <int>`**: Define el exponente del límite superior para el tamaño de la matriz, evaluado como `2^max_N`. El valor por defecto es `11` (evalúa hasta matrices de 2048x2048).

#### Ejemplos de Uso

```bash
# Compilar todo el ecosistema
./run compile

# Ejecutar benchmarks secuenciales hasta matrices de 4096x4096
./run test --max_N 12

# Ejecutar escalamiento paralelo (usa max_N=11 por defecto)
./run parallel_test

# Comprobar correctitud de los algoritmos
./run validate
```