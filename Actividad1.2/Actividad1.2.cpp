/*
Alejandro Rodriguez del Bosque - A01722329
TC1031 - Programacion de estructuras de datos y algoritmos fundamentales
3 de Septiembre 2023

Emplea metodos de ordenamiento y de busqueda en arreglos ordenados.
*/

#include <iostream>
#include <vector>
using namespace std;

/* 
* Ordena un vector<double> por orden numerico usando el metodo de Ordenamiento por Intercambio
*
*@Param (vector<double>& n) Valor del apuntado al vector que contiene la informacion
*
*@return N/A
*
*Complejidad de tiempo: O(n^2)
*Complejidad de espacio: O(n)
*/
void ordenaPorIntercambio(vector<double>& n){
    
    int s = n.size();

    for(int i = 1; i < s; i++){
        int key = n[i];
        int j = i-1;

        while(j >= 0 && n[j] > key){
            n[j+1] = n[j];
            j = j-1;
        }
        n[j+1] = key;
    }
}

/* 
* Ordena un vector<double> por orden numerico usando el metodo de Ordenamiento por Burbuja
*
*@Param (vector<double>& n) Valor del apuntador al vector que contiene la informacion
*
*@return N/A
*
*Complejidad de tiempo: O(n^2)
*Complejidad de espacio: O(n)
*/
void ordenaPorBurbuja(vector<double>& n){
    bool swapped = true;
    int size = n.size();
    
    while (swapped) {
        swapped = false;
        for (int i = 0; i < size - 1; i++) {
            if (n[i] > n[i + 1]) {
                int temp = n[i];
                n[i] = n[i + 1];
                n[i + 1] = temp;
                swapped = true;
            }
        }
        size--;
    }
}

/* 
* Ordena un vector<double> de cierta seccion a cierta seccion. Usado en conjunto con ordenaPorIntercambio
*
*@Param (vector<double>& n) Valor del apuntador al vector que contiene la informacion
*
*@return N/A
*
*Complejidad de tiempo: O(n)
*Complejidad de espacio: O(n)
*/
void merge(vector<double>& n, int left, int mid, int right){
    
    int n1 = mid - left + 1;
    int n2 = right - mid;
   
    vector<double> L(n1);
    vector<double> R(n2);

    for(int i = 0; i < n1; i++){
        L[i] = n[left+i];
    }
    for(int i = 0; i < n2; i++){
        R[i] = n[mid+1+i];
    }

    int i = 0;
    int j = 0;
    int k = left;

    
    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            n[k] = L[i];
            i++;
        }
        else{
            n[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        n[k] = L[i];
        i++;
        k++;
    }

    while(j < n2){
        n[k] = R[j];
        j++;
        k++;
    }
}

/* 
* Ordena un vector<double> por orden numerico usando el metodo de Ordenamiento por Merge
*
*@Param (vector<double>& n) Valor del apuntador al vector que contiene la informacion
* (int left) valor del indice minimo a ordenar
* (int right) valor del indice maximo a ordenar
*
*@return N/A
*
*Complejidad de tiempo: O(nLog(n))
*Complejidad de espacio: O(n)
*/
void ordenaPorMerge(vector<double>& n, int left, int right){
    if(left < right){

        int mid = left + (right - left) / 2;

        ordenaPorMerge(n, left, mid);
        ordenaPorMerge(n, mid+1, right);

        merge(n,left,mid,right);
    }
}

/* 
* Encuentra un numero en un vector<double> mediante el metodo de busqueda secuencial
*
*@Param (vector<double>& n) Valor del apuntador al vector que contiene la informacion
* (double target) numero que buscar
*
*@return indice donde se encuentra el numero o -1 si no existe en el arreglo
*
*Complejidad de tiempo: O(n)
*Complejidad de espacio: O(n)
*/
int busquedaSecuencial(vector<double> n, double target){
    for(int i = 0; i < n.size(); i++){
        if(n[i] == target){
            return i;
        }
    }
    return -1;
}

/* 
* Encuentra un numero en un vector<double> mediante el metodo de busqueda binaria
*
*@Param (vector<double>& n) Valor del apuntador al vector que contiene la informacion
* (double target) numero que buscar
*
*@return indice donde se encuentra el numero o -1 si no existe en el arreglo
*
*Complejidad de tiempo: O(Log(n))
*Complejidad de espacio: O(n)
*/
int busquedaBinaria(vector<double> n, double target){
    int left = 0;
    int right = n.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (n[mid] == target) {
            return mid; 
        } else if (n[mid] < target) {
            left = mid + 1; 
        } else {
            right = mid - 1; 
        }
    }

    return -1; 
}

int main(){
    vector<double> testBubble = {1,2,3,1,3,5,4,5};
    vector<double> testIntercambio = testBubble;
    vector<double> testMerge = testBubble;

    ordenaPorIntercambio(testIntercambio);
    ordenaPorBurbuja(testBubble);
    ordenaPorMerge(testMerge,0,testMerge.size()-1);

    cout << "Merge: ";
    for(int i = 0; i< testMerge.size(); i++){
        cout << " " << testMerge[i];
    }
    cout << endl;

    cout << "Bubble: ";
    for(int i = 0; i< testBubble.size(); i++){
        cout << " " << testBubble[i];
    }
    cout << endl;

    cout << "Intercambio: ";
    for(int i = 0; i< testIntercambio.size(); i++){
        cout << " " << testIntercambio[i];
    }
    cout << endl << "Busqueda Secuencial Indice en: " << busquedaSecuencial(testIntercambio, 4);
    cout << endl << "Busqueda Binaria Indice en: " << busquedaBinaria(testIntercambio, 4);

}