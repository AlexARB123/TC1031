#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;


    /*
    * @brief Convierte una fecha a un int64_t
    * 
    * @param string fecha a convertir
    * @return Fecha convertida en lista
    * @complexity Tiempo: O(1)
    */
int64_t stringDateToInteger(const string &dateString) {
  int year, month, day, hour, minute, second;

  // Create a stringstream to parse the input string
  istringstream iss(dateString);

  // Read components from the string
  iss >> year;

  // Read the abbreviated month name and convert it to a numerical value
  string monthStr;
  iss >> monthStr;
  const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                          "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  for (int i = 0; i < 12; i++) {
    if (monthStr == months[i]) {
      month = i + 1; // Months are 1-based
      break;
    }
  }

  iss >> day >> hour;
  char colon;
  iss >> minute >> colon >> second;

  // Create the sortable integer by concatenating components
  int64_t sortableDate = (year * 10000000000) + (month * 100000000) +
                     (day * 1000000) + (hour * 10000) + (minute * 100) + second;

  return sortableDate;
}

/**
 * @brief Clase que representa una entrada de registro.
 */
class LogEntry {  
    public:
        /**
         * @brief Constructor para entradas inválidas.
         * @param err Número que indica un error (en este caso, no se utiliza).
         */
        LogEntry(int err);
        LogEntry();

        /**
         * @brief Constructor que procesa una entrada de registro.
         * @param l La entrada de registro en formato string.
         */
        LogEntry(string l);

        string entry;   /**< La entrada de registro completa. */
        string date;   /**< La fecha */
        int64_t epoch_time; // Tiempo eludido usado para sortear
};

LogEntry :: LogEntry(int err){
    entry = "NA";
    date = "NA";
    epoch_time = 0;
}

LogEntry:: LogEntry(){
    entry = "NA";
    date = "NA";
    epoch_time = 0;
}

LogEntry ::LogEntry(string l) {
    entry = l;
    stringstream ss(l);
    vector<string> substrings;
    string substring;
    char delimeter = '|';

    while (getline(ss, substring, delimeter)) {
        substrings.push_back(substring);
    }

    date = substrings[0];
    epoch_time = stringDateToInteger(date);
}

template <class T>
class Node
{
public:
    T data;
    Node<T>* next;
    Node(T dataValue){
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

    int get_size(){return size;}
    LinkedList() {
        head = nullptr;
        size = 0;
    }

    Node<T>* get_head(){return head;}
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
            size++;
        }
        else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new_node;
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
                current = current->next;
            }
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

    /*
    * @brief Funcion de Merge para Merge Sort
    * 
    * @param (left) valor minimo del primer nodo
    * @param (right) valor maximo del nodo
    * @return Nodo con la lista mergeada
    * @complexity Tiempo: O(n log n)
    */
    Node<T>* merge(Node<T>* left, Node<T>* right) {
        Node<T>* result = nullptr;

        // Base cases: if either of the lists is empty, return the other list
        if (left == nullptr) {
            return right;
        }
        if (right == nullptr) {
            return left;
        }

        // Compare the values in both lists and merge them in ascending order
        if (left->data.epoch_time <= right->data.epoch_time) {
            result = left;
            result->next = merge(left->next, right);
        } else {
            result = right;
            result->next = merge(left, right->next);
        }

        return result;
    }
    
    /*
    * @brief Divide la lista en dos para merge sort
    * 
    * @param head primer nodo de la lista ligada
    * @param left valor del primer nodo de la primera parte de la division
    * @param righ valor del primer nodo de la segunda parte de la division
    * 
    * @complexity Tiempo: O(n)
    */
    void split(Node<T>* head, Node<T>*& left, Node<T>*& right) {
        Node<T>* slow = head;
        Node<T>* fast = head->next;

        // Advance 'fast' two steps, and 'slow' one step until 'fast' reaches the end
        while (fast != nullptr) {
            fast = fast->next;
            if (fast != nullptr) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        left = head;
        right = slow->next;
        slow->next = nullptr; // Split the list into two at 'slow'
    }
    
    /*
    * @brief Merge Sort para la lista ligada
    * 
    * @param Primer nodo de la lista
    * @return Sin retorno
    * @complexity Tiempo: O(n log n)
    */
    void mergeSort(Node<T>*& headRef) {
        Node<T>* head = headRef;
        Node<T>* left;
        Node<T>* right;

        if (head == nullptr || head->next == nullptr) {
            return; // Base case: already sorted or empty list
        }

        // Split the list into two halves
        split(head, left, right);

        // Recursively sort both halves
        mergeSort(left);
        mergeSort(right);

        // Merge the sorted halves
        headRef = merge(left, right);
    }

    /*
    * @brief Sortea la lista
    * @complexity Tiempo: O(n log n)
    */
    void sort() {
        mergeSort(head);
    }

};

    /*
    * @brief Lee el archivo y lo incluye en la lista ligada
    * 
    * @param data - Lista ligada al cual añadir
    * @param fileName - Nombre de Archivo a leer
    * 
    * @complexity Tiempo: O(n)
    */
void readFile(LinkedList<LogEntry>& data, string fileName){
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return;
    }

    string line;

    while (getline(file, line)) {
       LogEntry curr(line);
       data.create(curr);
    }

    file.close();

    return;
}
    /*
    * @brief Crea una lista ligada con el rango indicado
    * 
    * @param readList - Lista que leera
    * @param writeList - Lista que escribira
    * @param startTime - Tiempo minimo
    * @param endTime - Tiempo Maximo
    * 
    * @complexity Tiempo: O(n)
    */
void findRange(LinkedList<LogEntry>& readList, LinkedList<LogEntry>& writeList, int64_t startTime, int64_t endTime) {
    Node<LogEntry>* current = readList.get_head();
    bool withinRange = false;

    while (current != nullptr) {
        if (current->data.epoch_time >= startTime && current->data.epoch_time <= endTime) {
            writeList.create(current->data);
            withinRange = true;
        } else if (withinRange) {
            // If we were within the range and now we're not, we've collected all needed elements.
            break;
        }
        current = current->next;
    }
}

int main(){
    LinkedList<LogEntry> read;
    string fileName = "bitacoraelb.txt";
    cout << "READING" << endl;
    readFile(read, fileName);
    read.sort();

    ofstream outputFileTwo("output.txt");

    if (outputFileTwo.is_open()) {
        Node<LogEntry>* current = read.get_head();
        while (current != nullptr) {
            outputFileTwo << current->data.entry << endl;
            current = current->next;
        }
        outputFileTwo.close(); // Cerrar el flujo de archivo
        cout << "File 'output.txt' has been successfully written." << endl;
    } else {
        cerr << "Unable to open the file 'output.txt' for writing." << endl;
    }

    LinkedList<LogEntry> logs;
    int64_t first = stringDateToInteger("2020 Mar 01 03:46:04");
    int64_t last = stringDateToInteger("2020 Mar 31 19:07:31");
    findRange(read, logs, first, last);
    
    ofstream outputFile("outputFiltered.txt");

    if (outputFile.is_open()) {
        Node<LogEntry>* current = logs.get_head();
        while (current != nullptr) {
            outputFile << current->data.entry << endl;
            current = current->next;
        }
        outputFile.close(); // Cerrar el flujo de archivo
        cout << "File 'outputFiltered.txt' has been successfully written." << endl;
    } else {
        cerr << "Unable to open the file 'outputFiltered.txt' for writing." << endl;
    }

   
}
