# Algoritmos genéticos paralelos
## Link del vídeo: https://youtu.be/jHZrlqx6Jpw <br>

## Integrantes:
- Maximiliano Correa - 2161594
- Alfredo Nieto - 2200137
- Brayan Rojas - 2191942

## Contenido
- `original.cpp`: Código fuente de la solución secuencial en C++.
- `paralelizado2_0.cpp`: Código fuente de la solución paralela en C++ utilizando OpenMP.
- `original`: Ejecutable generado a partir de `original.cpp`.
- `paralelizado`: Ejecutable generado a partir de `paralelizado2_0.cpp`.

## Descripción
### Código Original

Este código en C++ implementa un algoritmo genético simple para evolucionar una población de cadenas de texto hasta que coincidan con una cadena objetivo. Pasando a la explicación detallada:

1-Inclusiones de encabezado:

![image](https://github.com/alfredonomiun/IntroPP2200137/assets/94908591/1db02154-82fd-4985-bd68-0bdb3c677cf0)

Estos son archivos de encabezado estándar de C++. El primero (<bits/stdc++.h>) es un encabezado de conveniencia que incluye la mayoría de los encabezados estándar de C++. El segundo (<chrono>) se utiliza para operaciones relacionadas con el tiempo.

2- Declaraciones de espacio de nombres:

![image](https://github.com/alfredonomiun/IntroPP2200137/assets/94908591/7814a8ae-a18b-4921-8c65-6e3cc4ccfcbe)

Este código utiliza el espacio de nombres std (estándar) y el espacio de nombres std::chrono para operaciones relacionadas con el tiempo.

3- Constantes

![image](https://github.com/alfredonomiun/IntroPP2200137/assets/94908591/4df2b7f5-60a3-4d8e-a30a-693cf01815f2)

Estas constantes definen el tamaño de la población, los genes válidos y la cadena objetivo.

4- Generación de números aleatorios:

![image](https://github.com/alfredonomiun/IntroPP2200137/assets/94908591/b6861e76-0bbb-40fa-b4a7-70e856c28f16)

![image](https://github.com/alfredonomiun/IntroPP2200137/assets/94908591/11ab034c-072b-4f16-9a2e-4b98e440af51)

Estas funciones se utilizan para generar números aleatorios dentro de un rango específico y obtener un gen seleccionado al azar para la mutación.

5- Generación de Cromosomas:

![image](https://github.com/alfredonomiun/IntroPP2200137/assets/94908591/80ce0c64-89b5-465c-bc8e-23abace42fdf)

Esta función crea un cromosoma aleatorio (cadena de genes) de la misma longitud que la cadena objetivo

6- Clase individual

![image](https://github.com/alfredonomiun/IntroPP2200137/assets/94908591/8a5294c8-1bf4-4273-8cba-02dea79b150a)

Esta clase representa a un individuo en la población. Contiene un cromosoma, puntaje de aptitud y métodos para inicializar un individuo, aparearse y calcular la aptitud.

7-Métodos de la Clase Individual:

*Individual::Individual(string chromosome): Constructor que inicializa un individuo con un cromosoma dado y calcula su aptitud.

*Individual Individual::mate(Individual parent2): Método para realizar apareamiento con otro individuo, produciendo una descendencia.

*int Individual::cal_fitness(): Método para calcular la aptitud de un individuo según qué tan cercano esté su cromosoma a la cadena objetivo.

8-Sobrecarga de Operadores:

![image](https://github.com/alfredonomiun/IntroPP2200137/assets/94908591/3643af9d-b38c-49fa-bc39-0245e3e60c26)

Esto sobrecarga el operador menor que (<) para comparar individuos según sus puntajes de aptitud.

9- Función Principal:

La función principal es donde se implementa el algoritmo genético. Inicializa la población, la hace evolucionar a lo largo de generaciones e imprime información sobre cada generación hasta que se alcanza la cadena objetivo.

10-Implementación del Algoritmo Genético:

*El bucle principal continúa hasta que se encuentra un individuo con una aptitud de 0 (coincidencia perfecta con la cadena objetivo).

*Se aplica el elitismo, donde el 10% superior de los individuos más aptos de la generación actual pasa directamente a la siguiente generación.

*El 90% restante de la nueva generación se crea mediante apareamiento de individuos de la generación actual, con alguna posibilidad de mutación para mantener la diversidad.

*Se imprime información sobre cada generación, incluido el número de generación, la mejor cadena en la población y su aptitud.

11-Medición del Tiempo de Ejecución:

*El programa registra los tiempos de inicio y finalización usando la biblioteca <chrono> para medir el tiempo de ejecución.

12-Salida:

*Se imprime información sobre cada generación, la mejor cadena y su aptitud en la consola.

*También se imprime el tiempo total de ejecución.

### Código Mejorado

Este código C++ también implementa un algoritmo genético similar al anterior, pero incorpora paralelismo mediante OpenMP (Open Multi-Processing) para realizar algunas operaciones en paralelo. A continuación, explicamos las adiciones y modificaciones relacionadas con OpenMP:

1- Inclusión de Encabezados Adicionales:

" #include <omp.h> "

Este encabezado incluye las funciones y directivas de OpenMP que se utilizan para realizar operaciones en paralelo.

2- Configuración del Número de Hilos:

"#pragma omp parallel num_threads(16)"

Esta línea establece el número de hilos para la sección paralela en 16. Puedes ajustar este número según la cantidad de núcleos disponibles en tu máquina.

3- Inicialización Paralela de la Población:

![image](https://github.com/alfredonomiun/IntroPP2200137/assets/94908591/327d3a44-220b-494c-bba8-41d94802d363)

En este bloque paralelo, se inicializa la población de manera concurrente utilizando la directiva #pragma omp for.

4-Cálculo de la Aptitud en Paralelo:

![image](https://github.com/alfredonomiun/IntroPP2200137/assets/94908591/dc9d4cfe-717d-4b2f-956a-42c5c3ac163a)

Esta línea calcula la aptitud de cada individuo en la población de forma paralela.

5- Ordenamiento de la Población en Paralelo:

![image](https://github.com/alfredonomiun/IntroPP2200137/assets/94908591/32f96640-6d44-47fe-a3b7-95e0cb21eba2)

La función de ordenamiento se ejecuta de manera secuencial dentro de una región de un solo hilo (#pragma omp single).

6-Comprobación de Condiciones en Paralelo:

![image](https://github.com/alfredonomiun/IntroPP2200137/assets/94908591/ebe544d0-864f-44ba-9c15-b3242b57e0b9)

La verificación de si se ha encontrado la solución se realiza de forma secuencial dentro de una región de un solo hilo.

7- Manejo de la Nueva Generación en Paralelo:

![image](https://github.com/alfredonomiun/IntroPP2200137/assets/94908591/64d90a71-2a58-403b-85b7-010922677003)

La creación de una parte de la nueva generación (mediante elitismo) se realiza de manera secuencial, mientras que el resto se realiza en paralelo.

8- Sección Crítica para Actualizar la Población:

![image](https://github.com/alfredonomiun/IntroPP2200137/assets/94908591/c422b9bd-a597-4278-82d1-ff347d562e29)

La actualización de la población con la nueva generación se realiza dentro de una sección crítica para evitar condiciones de carrera.

9-Impresión de Información en Paralelo:

![image](https://github.com/alfredonomiun/IntroPP2200137/assets/94908591/0c7ef61f-61e7-45dd-a3ae-b37664776f06)

La impresión de información sobre la generación actual se realiza de manera secuencial para evitar posibles conflictos en la salida.

10-Barra de Sincronización:

"#pragma omp barrier"

Esta línea garantiza que todos los hilos hayan llegado a este punto antes de continuar.


11- Incremento de la Generación en Paralelo:

"#pragma omp single
{
    generation++;
}"

El incremento del contador de generación se realiza de manera secuencial para evitar conflictos.


12-Medición del Tiempo de Ejecución:

"auto duration = duration_cast<milliseconds>(stop_time - start_time);"

El tiempo de ejecución se mide de la misma manera que en el código sin paralelismo.

Este código utiliza OpenMP para paralelizar algunas partes del algoritmo genético, aprovechando el poder de procesamiento multicore para mejorar el rendimiento en la creación y evaluación de la población. Tener en cuenta que el rendimiento real dependerá de la arquitectura de la máquina y de la cantidad de núcleos disponibles.

## Instrucciones de Compilación
Para compilar el código del archivo `original.cpp` se utiliza el siguiente comando:

```g++ -std=c++11 original -o original```

Para compilar el código del archivo `paralelizado2_0.cpp` se utiliza el siguiente comando:

```g++ -std=c++11 paralelizado2_0.cpp -o paralelizado```

Para ejecutar el programa secuencial se utiliza el comando:

```./original```

Para ejecutar el programa paralelizado se utiliza el comando:

```./paralelizado```

## Resultados
Para ambas pruebas se utilizó el mismo gen, un gen bastante amplio en concreto se utilizó la cadena "I love GeeksforGeeks " 27 veces, es decir, 567 caracteres.

Los resultados obtenidos por el programa del código original fueron los siguientes:
![image](images/resultadooriginal.jpeg)
Se puede ver que tardó 2177446 milisegundos e hizo un total de 779591 generaciones.

En cambio, los resultados dados por el programa del código paralelizado son los siguientes:
![image](images/resultadoparalelizado.jpeg)
Se puede ver que tardó 1299615 milisegundos e hizo un total de 627546 generaciones.

## Conclusiones
Se observó una diferencia notable entre los resultados del programa paralelizado y del programa original. El programa paralelizado es más rápido que el programa secuencial cuando se trabaja con un "TARGET" grande, esto es gracias a la capacidad del código paralelo distribuyendo el trabajo de manera eficiente y así aprovechar múltiples hilos y nucleos de CPU.
