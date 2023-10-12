/**
 * Nombre: Alejandro Rodriguez
 * Matrícula: A01722329
 * 
 * El program crea clases de Priority Queue y Double QUeue
 */

#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

/**
 * @brief PQ - clase de Priority Queue
 */
template<class T>
class PQ {
    private:
        vector<pair<T,int>> elements; // Asignar info como (data, prioridad)

    public:

    /**
     * @brief Crear nuevo elemento
     * @param e la clase a agregar
     * @param p su propiedad
     * @return no tiene retorno
     * 
     * Complejidad O(1)
     */
    void create(T e, int p){
        elements.push_back(make_pair(e,p));
    }
    
    /**
     * @brief Obtiene el elemento de ayor prioridad
     * @return La instancia del elemento de mayor prioridad
     * 
     * Complejidad O(n)
     */
    T read() const {
        
        // Checar si el queue NO esta vacio
        
        if (!elements.empty()) {
            int max_p = elements[0].second; // Asignar maximo prioridad
            int max_e = elements[0].first; // Su correspondiente tipo

            for (const auto& pair : elements) { // Checar todos los pairs a encontrar el de prioridad mas alta
                if (pair.second > max_p) {
                    max_p = pair.second;
                    max_e = pair.first;
                }
            }

            return max_e;
        }
        return -1; // Si la cola está vacía

    
    }
    /**
     * @brief Cambia la prioridad de un elemento
     * @param e el data a cambiar
     * @param p su nueva prioridad
     * @return sin valor de retorno
     * 
     * Complejidad O(n)
     */
    void update(T e, int p){
        for(auto&pair : elements){
            if(pair.first == e){
                pair.second = p;
            }
        }
    }
    /**
     * @brief Borra un elemento de la PQ
     * @param e elemento a eliminar
     * @return void
     */
    void del(T e) {
        auto del = remove_if(elements.begin(), elements.end(),[e](const pair<int, int>& pair) {
                                return pair.first == e;
                });

        elements.erase(del, elements.end());
    }
};

/**
 * @brief Class DQ, crea doble cola
 */

template<class T>
class DQ{
    private:
        vector<T> elements;

    public:

    /**
     * @brief Agregar elemento al final de la cola
     * @param e Data a agregar
     * @return no tiene retorno
     * Complejidad O(1)
     */
    void createEnd(T e){
        elements.push_back(e);
    }

    /**
     * @brief Agregar elemento a el principio de la cola
     * @param e Data a agregar
     * @return no tiene retorno
     * Complejidad O(1)
     */
    void createBeginning(T e){
        elements.insert(elements.begin(), e);
    }

    /**
     * @brief Obtiene el primer elemento de la cola
     * @return el primer elemento
     * Complejidad O(1)
     */
    T readTop() const {
        if(!elements.empty()){
            return elements.front();
        }
        return -1;
    }

    /**
     * @brief Obtiene el primer elemento de la cola
     * @return el primer elemento
     * Complejidad O(1)
     */
    T readBottom() const {
        if(!elements.empty()){
            return elements.back();
        }
        return -1;
    }

    /**
     * @brief Remplaza un elemento con otro
     * @param e1 el elemento original
     * @param e2 el elemento con el que se replaza
     * @return void
     * 
     * Complejidad O(1)
     */
    void update(T e1, T e2){
        for (auto& els : elements){
            if (els == e1){
                e1 = e2;
            }
        }
    }
    /**
     * @brief Elimina elemento de doble coloa
     * @param e elemento al eliminar
     * @return sin retorno
     * 
     * Complejidad O(1)
     */
    void del(T e) {
        elements.erase(remove(elements.begin(), elements.end(), e), elements.end());
    }
};

int main() {
    // Crear priority Queue vacia
    PQ<int> pqueue;
    pqueue.create(1,1);
    pqueue.create(2,2);
    pqueue.create(3,3);

    int max = pqueue.read();
    if(max == -1){
        cout << "Cola vacia" << endl;
    }
    else{
        cout << "Max: " << max << endl;
    }

    pqueue.update(2,5);
    pqueue.del(1);

    max = pqueue.read();
    if(max == -1){
        cout << "Cola vacia" << endl;
    }
    else{
        cout << "Max: " << max << endl;
    }

    DQ<int> dqueue;
    dqueue.createBeginning(1);
    dqueue.createEnd(2);
    dqueue.createEnd(3);

    int top = dqueue.readTop();
    int bottom = dqueue.readBottom();
    if(top == -1){
        cout << "No hay elementos" << endl;
    }
    else{
        cout << "Top: " << top << endl;
        cout << "Bottom: " << bottom << endl;
    }

    dqueue.update(2,5);
    dqueue.del(1);

    top = dqueue.readTop();
    bottom = dqueue.readBottom();

    if(top == -1){
        cout << "No hay elementos" << endl;
    }
    else{
        cout << "Top: " << top << endl;
        cout << "Bottom: " << bottom << endl;
    }

}