/*
Alejandro Rodriguez del Bosque - A01722329

Como voy a solucionar el problema:
Voy a usar una linked list para tener todos los valores de los strings
Usando un stack, voy a checar si se ocupa borrar un elemento o no y al final voy a regresar todos esos elementos a la linked list
que me dara el resultado
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
    Node<T>* tail;
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
            tail = new_node;
        }
        else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new_node;
            cout << "Successfully added " << current->next->data << " to the linked list" << endl;
            tail = new_node;
            size++;
        }
        
    }
    /*
    * @brief Agrega un nuevo elemento al principio de la lista
    * 
    * @param valor a agregar
    * @return No tiene valor de retorno
    * @complexity Tiempo: O(1)
    */
    void createAtBeginning(T value){
        Node<T>* new_node = new Node<T>(value);
        if (head == nullptr) {
            head = new_node;
            cout << "Successfully added " << head->data << " to the head of the linked list" << endl;
            size++;
            tail = new_node;
        }
        else{
            Node* tmp = head;
            head = new_node;
            new_node->next = tmp;
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

template <typename T>
class Stack {
    private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    Node* topNode;

    public:
        Stack() : topNode(nullptr) {}

        ~Stack() {
            while (!isEmpty()) {
                pop();
            }
        }

        bool isEmpty() const {
            return topNode == nullptr;
        }

        void push(const T& value) {
            Node* newNode = new Node(value);
            newNode->next = topNode;
            topNode = newNode;
        }

        void pop() {
            if (isEmpty()) {
                std::cerr << "Error: Trying to pop from an empty stack." << std::endl;
                return;
            }
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }

        T& top() {
            if (isEmpty()) {
                cerr << "Error: Trying to access the top element of an empty stack.";
                return topNode->data;
            }
            return topNode->data;
        }
};

/*
    * @brief Provee un string y separa cada linea por palabra
    * 
    * @param toRead: lista a llenar
    * @param line: linea a la que se separara
    * @return No tiene valor de retorno
    * @complexity Tiempo: O(n)
    */
void read(LinkedList<string>& toRead, string line){
    
    int currChar = 0;
    int stringSize = line.size();
    // For loop donde voy a correr mi code
    for(int i = 0; i < stringSize; i = currChar){
        
        // Encontrar curr string
        string currString = "";

        while(line[currChar] != ' '){
            currString = currString + line[currChar];
            currChar ++;
            
            if(currChar >= stringSize){
                toRead.create(currString);
                break;
            }

            toRead.create(currString);
            currChar++;
            currString = "";
        }
    }
}

/*
    * @brief Sortea el nuevo Linked List aplicando las condiciones
    * 
    * @param res: Lista para llenar resultado
    * @param line: Lista para leer objetos
    * @param key: string que determina cambio de linea
    * @return No tiene valor de retorno
    * @complexity Tiempo: O(n)
*/
void arrange(LinkedList<T>& res, string key, LinkedList<T>& line){
    Stack thisStack<string>;

    Node* currNode = line.head;
    
    // Traversar toda la linked list
    while(currNode->next != nullptr){
        
        // Checar que la siguiente linea no sea el key
        if(currNode->data == key){
            LinkedList<string> elementsToAdd;
            // Borrar currentStack completamente y agregar los elementos en el stack a la LinkedList
            while(!thisStack.isEmpty()){
                string curr = thisStack.top();
                elementsToAdd.createAtBeginning(curr);
                thisStack.pop();
            }

            for(Node* current = elementsToAdd.head; current; current = current->next){
                res.create(current->data);
            }
        }

        // Checar que el elemento no sea igual al elemento que actualmente se habita en esa posicion
        if(currNode ->data == thisStack.top()){
            
            // Si es igual voy saltando todos los que siguen que sean igual
            while(currNode->data == thisStack.top()){
                currNode = currNode->next;
            }
        }
        // Si el elemento no es igual al anterior, agregar el anterior al Stack
        else{
            thisStack.push(currNode->data);
        }
    }
}
int main(){
    cout << "Separador: ";
    string separador = "";  
    cin >> separador;
    
    cin.clear();

    cout << "Input Line: \n";
    string line = "B A C A B";
    getline(cin, line);

    line = "B A C A B";
    LinkedList<string> entry;
    read(entry,line);
    LinkedList<string> entry;
    arrange(res,key,test)
    test.print();
}