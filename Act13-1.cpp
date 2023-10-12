/**
 * Nombre y Matricula:
 * Angel Hernández Rojas A00836889
 * Alejandro Rodriguez del Bosque A01722329
 * Samuel González Vázquez A01412958
 * Fecha: 07/09/2023
 * Materia: Programación de Estructuras de Datos y Algoritmos Fundamentales
 * Profesor: Eduardo López Benítez
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;

/**
 * @brief Convierte una dirección IP en formato string a su representación numérica.
 * 
 * @param La dirección IP en formato string 
 * @return La dirección IP en formato numérico.
 * @complexity Tiempo: O(1) | Espacio: O(1)
 */
double convertIP(string s){
  string substring = "";
  char delimeter = '.';
  stringstream s2(s);
  double total = 0;
  int count = 3;
  
  while(getline(s2,substring,delimeter)){
    double num = stoi(substring);
    total = total + (num * pow(256,count));
    count--;
  }

  s2.clear();
  return total;
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

        /**
         * @brief Constructor que procesa una entrada de registro.
         * @param l La entrada de registro en formato string.
         */
        LogEntry(string l);

        string entry;   /**< La entrada de registro completa. */
        double IPRaw;   /**< La dirección IP en formato numérico. */
        string IPFull;  /**< La dirección IP en formato string. */
};

LogEntry :: LogEntry(int err){
    entry = "NA";
    IPRaw = 0;
    IPFull = "NA";
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

  IPFull = substrings[1];
  IPFull = IPFull.substr(5);

  IPRaw = convertIP(IPFull);
}

/**
 * @brief Lee un archivo y devuelve sus líneas como un vector de strings.
 * 
 * @param fileName El nombre del archivo.
 * @return Un vector de strings con cada línea del archivo.
 * @complexity Tiempo: O(n) | Espacio: O(n)
 */
vector<string> readFile(string fileName){
    vector<string> entries;
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return entries;
    }

    string line;

    while (getline(file, line)) {
       entries.push_back(line);
    }

    file.close();

    return entries;
}

/**
 * @brief Implementación del algoritmo de ordenamiento quicksort.
 * 
 * @param logs El vector de objetos LogEntry a ordenar.
 * @param left Índice izquierdo del rango a ordenar.
 * @param right Índice derecho del rango a ordenar.
 * @complexity Tiempo: O(n log n) | Espacio: O(log n)
 */
void quicksort(vector<LogEntry>& logs, int left, int right) {
    if (left < right) {
        int i = left, j = right;
        LogEntry pivot = logs[(i + j) / 2];

        while (i <= j) {
            while (logs[i].IPRaw < pivot.IPRaw)
                i++;
            while (logs[j].IPRaw > pivot.IPRaw)
                j--;
            if (i <= j) {
                swap(logs[i], logs[j]);
                i++;
                j--;
            }
        }

        quicksort(logs, left, j);
        quicksort(logs, i, right);
    }
}

/**
 * @brief Encuentra el rango de índices de entradas de registro con direcciones IP dentro del rango especificado.
 * 
 * @param logs El vector de objetos LogEntry ordenado por dirección IP.
 * @param low La dirección IP inferior del rango.
 * @param high La dirección IP superior del rango.
 * @return Un vector de dos elementos que contiene el índice de la primera y última entrada de registro dentro del rango.
 * @complexity Tiempo: O(log n) | Espacio: O(1)
 */
vector<int> findRange(vector<LogEntry> logs, string low, string high){
    vector<int> result = {-1, -1};
    double l = convertIP(low);
    int left = 0;
    int right = logs.size() - 1;

    // Buscar la primera ocurrencia del límite inferior
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (logs[mid].IPRaw == l) {
            result[0] = mid;
            right = mid - 1;  // Continuar buscando en el lado izquierdo
        } else if (logs[mid].IPRaw < l) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // Buscar la última ocurrencia del límite superior
    double h = convertIP(high);
    left = 0;
    right = logs.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (logs[mid].IPRaw == h) {
            result[1] = mid;
            left = mid + 1;   // Continuar buscando en el lado derecho
        } else if (logs[mid].IPRaw < h) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

int main() {
    vector<string> entries = readFile("bitacoraelb.txt");
    vector<LogEntry> logs;
    
    for(int i = 0; i < entries.size(); i++){
        LogEntry curr(entries[i]);
        logs.push_back(curr);
    }

    quicksort(logs, 0, logs.size() -1);

    vector<string> bot_top(2);
    
    cout << "ENTER TWO VALID IPs to be searched" << endl << "Enter lower bound" << endl;
    cin >> bot_top[0];
    cin.clear();

    cout << endl << "Enter higher bound" << endl;
    cin >> bot_top[1];
    cin.clear();
    
    vector<double> lohigh(2);

    for(int i = 0; i < bot_top.size(); i++){
        lohigh[i] = convertIP(bot_top[i]);
    }

    vector<int> range = findRange(logs, bot_top[0], bot_top[1]);
    
    cout <<endl << range[0] << "   " << range[1];
    if(range[0] <= range[1] && range[0] > -1 && range[1] > -1){
        for(int i = range[0]; i <= range[1]; i++){
            cout << logs[i].entry << endl;
        }
    }
    else{
        cout << "NO VALID IP DETECTED";
    }

    ofstream outputFile("output.txt");

    if (outputFile.is_open()) {
        for (int i = 0; i < logs.size(); i++) {
            outputFile << logs[i].entry << endl; // Escribir cada entrada seguida de un salto de línea
        }
        outputFile.close(); // Cerrar el flujo de archivo
        cout << "File 'output.txt' has been successfully written." << endl;
    } else {
        cerr << "Unable to open the file 'output.txt' for writing." << endl;
    }
    
    return 0;
}
