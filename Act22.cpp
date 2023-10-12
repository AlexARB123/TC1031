/**
 * Nombre: Angel Hernández Rojas
 * Matrícula: A00836889
 * Fecha: 02/10/2023
 * Carrera: Ingeniero en Robotica y Sistemas Digitales
 * Materia: Programación de Estructuras de Datos y Algoritmos Fundamentales
 * 
 * El programa define dos clases: PriorityQueue (Cola de Prioridad) y Deque (Doble Cola). Cada una de ellas
 * proporciona operaciones para crear, leer, actualizar y eliminar elementos.
 * 
 */


#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

/**
 * @brief Clase que implementa una Cola de Prioridad.
 */
class PriorityQueue {
private:
    vector<pair<int, int>> elements; // Par (elemento, prioridad)

public:
    /**
     * @brief Crea un nuevo elemento en la cola de prioridad.
     * @param elemento El elemento a agregar.
     * @param prioridad La prioridad del elemento.
     * @return void
     */
    void create(int elemento, int prioridad) {
        elements.push_back(make_pair(elemento, prioridad));
    }

    /**
     * @brief Lee el elemento con la mayor prioridad.
     * @return El elemento con la mayor prioridad, o -1 si la cola está vacía.
     */
    int read() const {
        if (!elements.empty()) {
            int max_priority = elements[0].second;
            int max_element = elements[0].first;

            for (const auto& pair : elements) {
                if (pair.second > max_priority) {
                    max_priority = pair.second;
                    max_element = pair.first;
                }
            }

            return max_element;
        }
        return -1; // Si la cola está vacía
    }

    /**
     * @brief Actualiza la prioridad de un elemento.
     * @param elemento El elemento cuya prioridad se actualizará.
     * @param nueva_prioridad La nueva prioridad del elemento.
     * @return void
     */
    void update(int elemento, int nueva_prioridad) {
        for (auto& pair : elements) {
            if (pair.first == elemento) {
                pair.second = nueva_prioridad;
            }
        }
    }

    /**
     * @brief Elimina un elemento de la cola de prioridad.
     * @param elemento El elemento a eliminar.
     * @return void
     */
    void del(int elemento) {
        auto it = remove_if(elements.begin(), elements.end(),
                                [elemento](const pair<int, int>& pair) {
                                    return pair.first == elemento;
                                });

        elements.erase(it, elements.end());
    }
};

/**
 * @brief Clase que implementa una Doble Cola (Deque).
 */
class Deque {
private:
    vector<int> elements;

public:
    /**
     * @brief Crea un nuevo elemento en la Doble Cola.
     * @param elemento El elemento a agregar.
     * @return void
     */
    void create(int elemento) {
        elements.push_back(elemento);
    }

    /**
     * @brief Lee el primer elemento de la Doble Cola.
     * @return El primer elemento, o -1 si la Doble Cola está vacía.
     */
    int read() const {
        if (!elements.empty()) {
            return elements.front();
        }
        return -1; // Si la Doble Cola está vacía
    }

    /**
     * @brief Actualiza un elemento de la Doble Cola.
     * @param elemento El elemento a actualizar.
     * @param nuevo_elemento El nuevo valor del elemento.
     * @return void
     */
    void update(int elemento, int nuevo_elemento) {
        for (auto& elem : elements) {
            if (elem == elemento) {
                elem = nuevo_elemento;
            }
        }
    }

    /**
     * @brief Elimina un elemento de la Doble Cola.
     * @param elemento El elemento a eliminar.
     * @return void
     */
    void del(int elemento) {
        elements.erase(remove(elements.begin(), elements.end(), elemento), elements.end());
    }
};

int main() {
    PriorityQueue pq;
    pq.create(10, 3);
    pq.create(20, 2);
    pq.create(30, 1);

    int max_pq = pq.read();
    if (max_pq != -1) {
        cout << "PriorityQueue - Max elemento: " << max_pq << endl;
    } else {
        cout << "PriorityQueue - La cola está vacía" << endl;
    }

    pq.update(20, 4);

    max_pq = pq.read();
    if (max_pq != -1) {
        cout << "PriorityQueue - Max elemento despues de actualizar: " << max_pq << endl;
    } else {
        cout << "PriorityQueue - La cola está vacia" << endl;
    }

    pq.del(10);
    max_pq = pq.read();
    if (max_pq != -1) {
        cout << "PriorityQueue - Max elemento despues de eliminar: " << max_pq << endl;
    } else {
        cout << "PriorityQueue - La cola está vacia" << endl;
    }

    Deque dq;
    dq.create(100);
    dq.create(200);
    dq.create(300);

    int first_dq = dq.read();
    if (first_dq != -1) {
        cout << "Deque - Primer elemento: " << first_dq << endl;
    } else {
        cout << "Deque - El Deque está vacio" << endl;
    }

    dq.update(200, 400);
    first_dq = dq.read();
    if (first_dq != -1) {
        cout << "Deque - Primer elemento despues de actualizar: " << first_dq << endl;
    } else {
        cout << "Deque - El Deque está vacio" << endl;
    }

    dq.del(100);
    first_dq = dq.read();
    if (first_dq != -1) {
        cout << "Deque - Primer elemento despues de eliminar: " << first_dq << endl;
    } else {
        cout << "Deque - El Deque está vacio" << endl;
    }

    return 0;
}
