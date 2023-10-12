#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;


// Function to convert a string date to a sortable integer
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

    void sort() {
        mergeSort(head);
    }

};

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

int main(){
    LinkedList<LogEntry> read;
    string fileName = "bitacoraelb.txt";
    cout << "READING" << endl;
    readFile(read, fileName);
    read.sort();
    ofstream outputFile("output.txt");

    if (outputFile.is_open()) {
        Node<LogEntry>* current = read.get_head();
        while (current != nullptr) {
            outputFile << current->data.entry << endl;
            current = current->next;
        }
        outputFile.close(); // Cerrar el flujo de archivo
        cout << "File 'output.txt' has been successfully written." << endl;
    } else {
        cerr << "Unable to open the file 'output.txt' for writing." << endl;
    }
}
