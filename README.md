[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/5zgGDtf4)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-2e0aaae1b6195c2367325f4f02e2d04e9abb55f0b24a779b69b11b9e10269abc.svg)](https://classroom.github.com/online_ide?assignment_repo_id=21729039&assignment_repo_type=AssignmentRepo)
# Tarea de Grafos

## Integrantes:
- 1 Eliseo David Velasquez Diaz
- 2 Jean Luka Terrazo Santiago

## Objetivo: 
El objetivo de esta tarea es implementar un **Path Finder** para la ciudad de Lima. 

<p align="center">
    <img src=https://github.com/utec-cs-aed/homework_graph/assets/79115974/b63f69db-17eb-417a-8aa1-8483d8dcdaf0 / >
</p>

## Dependencias

Para esta tarea se solicita utilizar ```C++17``` y la librería ```SFML 2.5```

- Para instalar ```SFML 2.5```:

    - [Windows](https://www.youtube.com/watch?v=HkPRG0vfObc)
    - [MacOS y Linux](https://www.youtube.com/playlist?list=PLvv0ScY6vfd95GMoMe2zc4ZgGxWYj3vua)

Cuando se instale la librería, probar que las siguientes líneas del ```CMakeLists.txt``` encuentren la librería adecuadamente.
```cmake
find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)
if(SFML_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window)
else()
    message("SFML not found")
endif()
```

## Dataset
El dataset consiste de dos csv:

- *nodes.csv*

    ![image](https://github.com/utec-cs-aed/homework_graph/assets/79115974/6a68cf06-196a-4605-83a7-3183e9a3f0ec)


- *edges.csv*

    ![image](https://github.com/utec-cs-aed/homework_graph/assets/79115974/247bbbd7-6203-45f4-8196-fcb0434b0f1d)


## Algoritmos
Se les solicita implementar tres algoritmos para busqueda en grafos

- *Dijkstra*

- *Best First Search*

- *A**

Además:
- Analice la complejidad computacional de los tres algoritmos de acuerdo a su propia implementación.
- Puede considere como heuristica la distancia en linea recta.
- **Debe realizar un pequeño video (2 min) mostrando la funcionalidad visual de cada algoritmo**

## Diagrama de clases UML

![image](https://github.com/utec-cs-aed/homework_graph/assets/79115974/f5a3d89e-cb48-4715-b172-a17e6e27ee24)

----------

## Implementación Completada

### Algoritmos Implementados ✅

Se han implementado los tres algoritmos solicitados:

1. **Dijkstra** - Encuentra el camino más corto garantizado
2. **Best First Search** - Búsqueda informada usando solo heurística
3. **A*** - Combinación óptima de costo real y heurística

### Características de la Implementación

- ✅ Todos los algoritmos funcionan correctamente
- ✅ Visualización paso a paso con animación
- ✅ Diferentes colores para cada algoritmo:
  - **Dijkstra**: Azul (100, 100, 255)
  - **Best First Search**: Verde (100, 255, 100)
  - **A***: Rojo (255, 100, 100)
  - **Camino final**: Dorado (255, 215, 0)
- ✅ Heurística: Distancia euclidiana en línea recta
- ✅ Análisis de complejidad computacional completo

### Cómo Compilar y Ejecutar

#### Requisitos Previos
- C++17 o superior
- SFML 2.5 instalado correctamente
- CMake 3.10 o superior

#### Compilación (Windows)

```bash
# Crear directorio de build
mkdir build
cd build

# Configurar con CMake
cmake ..

# Compilar
cmake --build . --config Release

# Ejecutar
./Release/homework_graph.exe
```

#### Compilación (Linux/macOS)

```bash
# Crear directorio de build
mkdir build
cd build

# Configurar y compilar
cmake ..
make

# Ejecutar
./homework_graph
```

### Cómo Usar el Programa

1. **Seleccionar nodo origen**: Click izquierdo en el mapa (se marca en verde)
2. **Seleccionar nodo destino**: Segundo click izquierdo (se marca en cyan)
3. **Ejecutar algoritmos**:
   - Presionar `D` para **Dijkstra**
   - Presionar `B` para **Best First Search**
   - Presionar `A` para **A***
4. **Otras teclas**:
   - `E` - Mostrar/ocultar todas las aristas exploradas
   - `R` - Resetear (limpiar selección y resultados)
   - `Q` - Salir del programa

### Estructura del Proyecto

```
.
├── CMakeLists.txt              # Configuración de compilación
├── README.md                   # Este archivo
├── ANALISIS_COMPLEJIDAD.md     # Análisis detallado de complejidad
├── main.cpp                    # Punto de entrada
├── node.h                      # Estructura de nodos/vértices
├── edge.h                      # Estructura de aristas
├── graph.h                     # Clase Graph
├── path_finding_manager.h      # Implementación de algoritmos
├── gui.h                       # Interfaz gráfica
├── window_manager.h            # Gestor de ventana SFML
├── nodes.csv                   # Dataset de nodos (8.1 MB)
└── edges.csv                   # Dataset de aristas (33.3 MB)
```

### Análisis de Complejidad

Ver el archivo [ANALISIS_COMPLEJIDAD.md](ANALISIS_COMPLEJIDAD.md) para un análisis detallado de:
- Complejidad temporal y espacial de cada algoritmo
- Comparación entre los tres algoritmos
- Justificación de la implementación
- Casos de uso recomendados

### Detalles Técnicos

**Estructuras de Datos Utilizadas:**
- `std::set<Entry>` - Cola de prioridad para todos los algoritmos
- `std::unordered_map<Node*, Node*>` - Almacenar padres para reconstruir camino
- `std::unordered_map<Node*, double>` - Almacenar distancias/scores

**Ventajas de std::set:**
- Inserción: O(log n)
- Eliminación: O(log n)
- Acceso al mínimo: O(1)
- Perfecto para colas de prioridad

### Video de Demostración

**Video demostrativo:** [Ver video en Google Drive](https://drive.google.com/file/d/1xUwj-5Tb5AKu7CbiDCY-1Vj9XNxbvPQL/view?usp=sharing)

### Notas Adicionales

- El dataset contiene el mapa real de Lima con ~250,000 nodos y ~790,000 aristas
- La visualización incluye sleep de 10ms para apreciar el algoritmo en acción
- El camino final se destaca en color dorado con grosor aumentado
- La heurística euclidiana es admisible y consistente para A*

----------
> **Créditos:** Juan Diego Castro Padilla [juan.castro.p@utec.edu.pe](mailto:juan.castro.p@utec.edu.pe)




