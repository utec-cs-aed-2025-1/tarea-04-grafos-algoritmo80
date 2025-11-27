//
// Created by juan-diego on 3/29/24.
//

#ifndef HOMEWORK_GRAPH_PATH_FINDING_MANAGER_H
#define HOMEWORK_GRAPH_PATH_FINDING_MANAGER_H


#include "window_manager.h"
#include "graph.h"
#include <unordered_map>
#include <set>


// Este enum sirve para identificar el algoritmo que el usuario desea simular
enum Algorithm {
    None,
    Dijkstra,
    BestFirstSearch,
    AStar
};


//* --- PathFindingManager ---
//
// Esta clase sirve para realizar las simulaciones de nuestro grafo.
//
// Variables miembro
//     - path           : Contiene el camino resultante del algoritmo que se desea simular
//     - visited_edges  : Contiene todas las aristas que se visitaron en el algoritmo, notar que 'path'
//                        es un subconjunto de 'visited_edges'.
//     - window_manager : Instancia del manejador de ventana, es utilizado para dibujar cada paso del algoritmo
//     - src            : Nodo incial del que se parte en el algoritmo seleccionado
//     - dest           : Nodo al que se quiere llegar desde 'src'
//*
class PathFindingManager {
    WindowManager *window_manager;
    std::vector<sfLine> path;
    std::vector<sfLine> visited_edges;

    struct Entry {
        Node* node;
        double dist;

        bool operator < (const Entry& other) const {
            return dist < other.dist;
        }
    };

    // Función heurística: distancia euclidiana en línea recta
    double heuristic(Node* a, Node* b) {
        double dx = a->coord.x - b->coord.x;
        double dy = a->coord.y - b->coord.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    void dijkstra(Graph &graph) {
        std::unordered_map<Node *, Node *> parent;
        std::unordered_map<Node *, double> dist;
        std::set<Entry> pq;

        // Inicializar distancias
        for (auto &[id, node] : graph.nodes) {
            dist[node] = std::numeric_limits<double>::max();
        }

        dist[src] = 0.0;
        pq.insert({src, 0.0});
        parent[src] = nullptr;

        while (!pq.empty()) {
            Entry current = *pq.begin();
            pq.erase(pq.begin());

            Node* u = current.node;

            // Si llegamos al destino, podemos terminar
            if (u == dest) {
                break;
            }

            // Explorar vecinos
            for (Edge* edge : u->edges) {
                Node* v = (edge->src == u) ? edge->dest : edge->src;
                double weight = edge->length;

                if (dist[u] + weight < dist[v]) {
                    // Remover la entrada antigua si existe
                    auto it = pq.find({v, dist[v]});
                    if (it != pq.end()) {
                        pq.erase(it);
                    }

                    // Actualizar distancia y padre
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.insert({v, dist[v]});

                    // Agregar arista visitada para visualización
                    visited_edges.push_back(sfLine(u->coord, v->coord, sf::Color(100, 100, 255), 1.2f));
                    render();
                }
            }
        }

        set_final_path(parent);
    }

    void best_first_search(Graph &graph) {
        std::unordered_map<Node *, Node *> parent;
        std::unordered_map<Node *, bool> visited;
        std::set<Entry> pq;

        // Inicializar
        pq.insert({src, heuristic(src, dest)});
        parent[src] = nullptr;
        visited[src] = false;

        while (!pq.empty()) {
            Entry current = *pq.begin();
            pq.erase(pq.begin());

            Node* u = current.node;

            // Si ya fue visitado, continuar
            if (visited[u]) {
                continue;
            }
            visited[u] = true;

            // Si llegamos al destino, terminamos
            if (u == dest) {
                break;
            }

            // Explorar vecinos
            for (Edge* edge : u->edges) {
                Node* v = (edge->src == u) ? edge->dest : edge->src;

                if (!visited[v]) {
                    if (parent.find(v) == parent.end()) {
                        parent[v] = u;
                        double h = heuristic(v, dest);
                        pq.insert({v, h});

                        // Agregar arista visitada para visualización
                        visited_edges.push_back(sfLine(u->coord, v->coord, sf::Color(100, 255, 100), 1.2f));
                        render();
                    }
                }
            }
        }

        set_final_path(parent);
    }

    void a_star(Graph &graph) {
        std::unordered_map<Node *, Node *> parent;
        std::unordered_map<Node *, double> g_score; // Costo real desde src
        std::unordered_map<Node *, double> f_score; // g_score + heurística
        std::set<Entry> pq;

        // Inicializar scores
        for (auto &[id, node] : graph.nodes) {
            g_score[node] = std::numeric_limits<double>::max();
            f_score[node] = std::numeric_limits<double>::max();
        }

        g_score[src] = 0.0;
        f_score[src] = heuristic(src, dest);
        pq.insert({src, f_score[src]});
        parent[src] = nullptr;

        while (!pq.empty()) {
            Entry current = *pq.begin();
            pq.erase(pq.begin());

            Node* u = current.node;

            // Si llegamos al destino, terminamos
            if (u == dest) {
                break;
            }

            // Explorar vecinos
            for (Edge* edge : u->edges) {
                Node* v = (edge->src == u) ? edge->dest : edge->src;
                double weight = edge->length;
                double tentative_g_score = g_score[u] + weight;

                if (tentative_g_score < g_score[v]) {
                    // Remover entrada antigua si existe
                    auto it = pq.find({v, f_score[v]});
                    if (it != pq.end()) {
                        pq.erase(it);
                    }

                    // Actualizar scores y padre
                    parent[v] = u;
                    g_score[v] = tentative_g_score;
                    f_score[v] = g_score[v] + heuristic(v, dest);
                    pq.insert({v, f_score[v]});

                    // Agregar arista visitada para visualización
                    visited_edges.push_back(sfLine(u->coord, v->coord, sf::Color(255, 100, 100), 1.2f));
                    render();
                }
            }
        }

        set_final_path(parent);
    }

    //* --- render ---
    // En cada iteración de los algoritmos esta función es llamada para dibujar los cambios en el 'window_manager'
    void render() {
        sf::sleep(sf::milliseconds(1));

        // Limpiar la ventana
        window_manager->clear();

        // Dibujar el grafo base
        window_manager->get_window().clear(sf::Color::Black);

        // Dibujar las aristas visitadas hasta ahora
        for (const sfLine &line : visited_edges) {
            line.draw(window_manager->get_window(), sf::RenderStates::Default);
        }

        // Dibujar el camino parcial si existe
        for (const sfLine &line : path) {
            line.draw(window_manager->get_window(), sf::RenderStates::Default);
        }

        // Dibujar nodos src y dest
        if (src != nullptr) {
            src->draw(window_manager->get_window());
        }
        if (dest != nullptr) {
            dest->draw(window_manager->get_window());
        }

        // Mostrar el frame
        window_manager->display();
    }

    //* --- set_final_path ---
    // Esta función se usa para asignarle un valor a 'this->path' al final de la simulación del algoritmo.
    // 'parent' es un std::unordered_map que recibe un puntero a un vértice y devuelve el vértice anterior a el,
    // formando así el 'path'.
    //
    // ej.
    //     parent(a): b
    //     parent(b): c
    //     parent(c): d
    //     parent(d): NULL
    //
    // Luego, this->path = [Line(a.coord, b.coord), Line(b.coord, c.coord), Line(c.coord, d.coord)]
    //
    // Este path será utilizado para hacer el 'draw()' del 'path' entre 'src' y 'dest'.
    //*
    void set_final_path(std::unordered_map<Node *, Node *> &parent) {
        Node* current = dest;

        // Limpiar el path anterior
        path.clear();

        // Si no hay camino al destino
        if (parent.find(dest) == parent.end() || (parent[dest] == nullptr && dest != src)) {
            return;
        }

        // Reconstruir el camino desde dest hasta src
        while (current != nullptr && parent.find(current) != parent.end()) {
            Node* prev = parent[current];
            if (prev != nullptr) {
                // Agregar la línea del camino con color destacado (amarillo/dorado)
                path.push_back(sfLine(prev->coord, current->coord, sf::Color(255, 215, 0), 2.5f));
            }
            current = prev;
        }
    }

public:
    Node *src = nullptr;
    Node *dest = nullptr;

    explicit PathFindingManager(WindowManager *window_manager) : window_manager(window_manager) {}

    void exec(Graph &graph, Algorithm algorithm) {
        if (src == nullptr || dest == nullptr) {
            return;
        }

        // Limpiar datos previos
        path.clear();
        visited_edges.clear();

        // Ejecutar el algoritmo correspondiente
        switch (algorithm) {
            case Dijkstra:
                dijkstra(graph);
                break;
            case BestFirstSearch:
                best_first_search(graph);
                break;
            case AStar:
                a_star(graph);
                break;
            default:
                break;
        }
    }

    void reset() {
        path.clear();
        visited_edges.clear();

        if (src) {
            src->reset();
            src = nullptr;
            // ^^^ Pierde la referencia luego de restaurarlo a sus valores por defecto
        }
        if (dest) {
            dest->reset();
            dest = nullptr;
            // ^^^ Pierde la referencia luego de restaurarlo a sus valores por defecto
        }
    }

    void draw(bool draw_extra_lines) {
        // Dibujar todas las aristas visitadas
        if (draw_extra_lines) {
            for (sfLine &line: visited_edges) {
                line.draw(window_manager->get_window(), sf::RenderStates::Default);
            }
        }

        // Dibujar el camino resultante entre 'str' y 'dest'
        for (sfLine &line: path) {
            line.draw(window_manager->get_window(), sf::RenderStates::Default);
        }

        // Dibujar el nodo inicial
        if (src != nullptr) {
            src->draw(window_manager->get_window());
        }

        // Dibujar el nodo final
        if (dest != nullptr) {
            dest->draw(window_manager->get_window());
        }
    }
};


#endif //HOMEWORK_GRAPH_PATH_FINDING_MANAGER_H
