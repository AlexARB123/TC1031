/*
Como voy a solucionar el problema:
Voy a utilizar un Stack para checar la repeticion de palabras.
La idea es ir fragmentando un Stack por segmento de oracion incluyendo el separador.
Para hacer eso creare una lista ligada de tipo stack para irlos separando por separador
Asi mismo, voy a usar un metodo para ir eliminando todas las palabras que van repetidas seguidas dentro del objeto stack
La idea es que encuentre una palabra, resuelva todas las que estan seguidas y vuelva a checar palabra anterior para ver si esta repetida
Idealmente, complejidad de O(n)
*/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

template <class T>
class Node
{
public:
    T data;
    Node<T>* next;
    Node(T dataValue) {
        data = dataValue;
        next = nullptr;
    }

};

template <class T>
class LinkedList {
private:
    Node<T>* head;
    int size;
public:
    LinkedList() {
        head = nullptr;
        size = 0;
    }

    /*
    * @brief Crea un nuevo elemento y lo anexa al final de la lista ligada
    * 
    * @param Valor a agregar a la lista ligada
    * @return No tiene valor de retorno
    * @complexity Tiempo: O(n)
    */
    void create(T value) {
        Node<T>* new_node = new Node<T>(value);
        if (head == nullptr) {
            head = new_node;
            cout << "Successfully added " << head->data << " to the head of the linked list" << endl;
            size++;
        }
        else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new_node;
            cout << "Successfully added " << current->next->data << " to the linked list" << endl;
            size++;
        }
        
    }
    
    /*
    * @brief Imprime todos los elementos de la lista ligada
    * 
    * @param No tiene parametros
    * @return No tiene valor de retorno
    * @complexity Tiempo: O(n)
    */
    void print(){
        if (head == nullptr) {
            cout << "No elements in the list" << endl;
        }
        else{
            Node<T>* current = head;
            while(current->next != nullptr){
                cout << current->data << endl;
                current = current->next;
            }
            cout << current->data << endl;
        }
    }
    
    /*
    * @brief Borra un numero de la lista ligada
    * 
    * @param Indice del valor a borrar
    * @return No tiene valor de retorno
    * @complexity Tiempo: O(n)
    */
    void del(int index){
        if (index < 0 || index >= size) {
            // Index out of bounds, do nothing
            return;
        }

        if (index == 0) {
            // If removing the head, update the head pointer
            Node<T>* temp = head;
            head = head->next;
            cout << "Succesfully deleted head" << endl;
            delete temp;
            size--;
            return;
        }

        Node<T>* current = head;
        Node<T>* previous = nullptr;
        int currentIndex = 0;

        while (current && currentIndex < index) {
            previous = current;
            current = current->next;
            currentIndex++;
        }

        if (current) {
            previous->next = current->next;
            delete current;
            size--;
            cout << "Deleted item at index " << index << endl;
        }
    }

    /*
    * @brief Modifica un elemento de la lista ligada
    * 
    * @param (Index) Indice al valor de modificar
    *        (newDat) valor que va a remplazar
    * @return No tiene valor de retorno
    * @complexity Tiempo: O(n)
    */
    void update(int Index, T newDat){
        if(Index >= size){
            cout << "Index exceeds size" << endl;
        }
        else{
            Node<T>* current = head;
            for(int i = 0; i < Index; i++){
                current = current ->next;
            }
            current->data = newDat;
            cout << "Updated item at index " << Index << endl;
        }
    }

    /*
    * @brief Obtiene uno de los elementos de la lista ligada
    * 
    * @param Indice del valor de obtener
    * @return El valor que se encuentra en la lista ligada
    * @complexity Tiempo: O(n)
    */
    T read(int Index){
        if(Index >= size){
            cout << "Index exceeds size" << endl;
        }
        else{
            Node<T>* current = head;
            for(int i = 0; i < Index; i++){
                current = current ->next;
            }
            return current->data;
        }
    }
};

int main(){
    cout << "Separador: ";
    string separador = "";  
    cin >> separador;
    
    cin.clear();

    cout << "Input Line: \n";
    string line;
    getline(cin, line);
}