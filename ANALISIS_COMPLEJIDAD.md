# Análisis de Complejidad Computacional

## 1. Algoritmo de Dijkstra

### Descripción
El algoritmo de Dijkstra encuentra el camino más corto desde un nodo fuente a todos los demás nodos en un grafo con pesos no negativos. Utiliza una cola de prioridad para explorar siempre el nodo con la menor distancia acumulada.

### Implementación
- **Estructura de datos**: `std::set<Entry>` como cola de prioridad
- **Operaciones principales**:
  - Inicialización de distancias: O(V)
  - Extracción del mínimo de la cola: O(log V)
  - Relajación de aristas: O(log V) por inserción/eliminación

### Complejidad Temporal
- **Peor caso**: **O((V + E) log V)**
  - V = número de vértices
  - E = número de aristas
  - Cada vértice se extrae de la cola una vez: O(V log V)
  - Cada arista se procesa una vez: O(E log V)

### Complejidad Espacial
- **O(V)**: Para almacenar las estructuras de datos:
  - `parent`: O(V)
  - `dist`: O(V)
  - `pq` (cola de prioridad): O(V)
  - `visited_edges` (visualización): O(E)

### Características
- **Garantiza el camino óptimo** si todos los pesos son no negativos
- **No requiere conocer el destino** de antemano
- **Explora en todas direcciones** desde el origen

---

## 2. Algoritmo Best First Search

### Descripción
Best First Search es un algoritmo de búsqueda informada que utiliza únicamente la función heurística (distancia euclidiana al destino) para priorizar qué nodo explorar siguiente. A diferencia de Dijkstra, no considera el costo acumulado.

### Implementación
- **Estructura de datos**: `std::set<Entry>` como cola de prioridad
- **Heurística**: Distancia euclidiana en línea recta al destino
- **Operaciones principales**:
  - Selección del nodo con menor h(n): O(log V)
  - Inserción de vecinos: O(log V)

### Complejidad Temporal
- **Peor caso**: **O((V + E) log V)**
  - Similar a Dijkstra en el peor caso
  - En el peor caso, explora todos los nodos
- **Mejor caso**: **O(E log V)**
  - Si la heurística guía bien hacia el objetivo
  - Puede encontrar un camino rápidamente

### Complejidad Espacial
- **O(V)**: Para almacenar:
  - `parent`: O(V)
  - `visited`: O(V)
  - `pq` (cola de prioridad): O(V)
  - `visited_edges` (visualización): O(E)

### Características
- **NO garantiza el camino óptimo**: Solo usa heurística, ignora costos reales
- **Puede ser muy rápido** si la heurística es buena
- **Codicia**: Siempre elige el nodo que "parece" más cercano al objetivo
- **Útil para exploración rápida** cuando la optimidad no es crítica

---

## 3. Algoritmo A* (A-Star)

### Descripción
A* es un algoritmo de búsqueda informada que combina las ventajas de Dijkstra y Best First Search. Utiliza una función de evaluación f(n) = g(n) + h(n), donde:
- g(n) = costo real acumulado desde el inicio (como Dijkstra)
- h(n) = estimación heurística del costo al destino (como Best First Search)

### Implementación
- **Estructura de datos**: `std::set<Entry>` como cola de prioridad
- **Heurística**: Distancia euclidiana (admisible y consistente)
- **Función de evaluación**: f(n) = g(n) + h(n)
- **Operaciones principales**:
  - Extracción del mínimo f(n): O(log V)
  - Actualización de g_score y f_score: O(log V)

### Complejidad Temporal
- **Peor caso**: **O((V + E) log V)**
  - Similar a Dijkstra cuando h(n) = 0
- **Caso promedio**: **O(b^d)** donde:
  - b = factor de ramificación efectivo
  - d = profundidad de la solución
  - Significativamente mejor que Dijkstra en la práctica

### Complejidad Espacial
- **O(V)**: Para almacenar:
  - `parent`: O(V)
  - `g_score`: O(V)
  - `f_score`: O(V)
  - `pq` (cola de prioridad): O(V)
  - `visited_edges` (visualización): O(E)

### Características
- **Garantiza el camino óptimo** si la heurística es admisible (nunca sobreestima)
- **Más eficiente que Dijkstra**: Explora menos nodos irrelevantes
- **Equilibrio perfecto**: Combina costo real y estimación
- **Óptimo y completo**: Encuentra la mejor solución si existe

---

## Comparación de los Tres Algoritmos

| Algoritmo | Complejidad Temporal | Garantía de Optimalidad | Uso de Heurística | Velocidad Práctica |
|-----------|---------------------|------------------------|-------------------|-------------------|
| **Dijkstra** | O((V + E) log V) | ✓ Sí | ✗ No | Moderada |
| **Best First Search** | O((V + E) log V)* | ✗ No | ✓ Sí (solo h) | Rápida* |
| **A*** | O((V + E) log V) | ✓ Sí** | ✓ Sí (g + h) | Muy rápida** |

*Best First puede ser muy rápido pero NO garantiza optimalidad
**A* garantiza optimalidad si la heurística es admisible

### Observaciones Prácticas

1. **Dijkstra**:
   - Mejor cuando se necesitan caminos a múltiples destinos
   - No requiere conocimiento del destino
   - Explora uniformemente en todas direcciones

2. **Best First Search**:
   - Muy rápido para encontrar "un" camino (no necesariamente el mejor)
   - Útil en juegos y simulaciones donde la velocidad es más importante que la optimidad
   - Puede fallar gravemente si la heurística es mala

3. **A***:
   - **El mejor de los tres mundos** cuando la heurística es buena
   - Óptimo para pathfinding en mapas 2D/3D
   - Usado en GPS, videojuegos, robótica
   - Explora solo las regiones relevantes del grafo

### Heurística Utilizada

En nuestra implementación, la función heurística es la **distancia euclidiana**:

```cpp
h(a, b) = √((ax - bx)² + (ay - by)²)
```

Esta heurística es:
- **Admisible**: Nunca sobreestima el costo real (la línea recta es el camino más corto)
- **Consistente**: h(a, c) ≤ costo(a, b) + h(b, c)
- **Apropiada para grafos geográficos** como el mapa de Lima

---

## Conclusión

Para el problema de pathfinding en el mapa de Lima:
- **A* es la mejor opción**: Combina optimalidad con eficiencia
- **Dijkstra es confiable**: Siempre encuentra el camino óptimo pero es más lento
- **Best First Search es arriesgado**: Rápido pero puede dar rutas subóptimas

La implementación con `std::set` proporciona operaciones logarítmicas eficientes para todos los algoritmos.
