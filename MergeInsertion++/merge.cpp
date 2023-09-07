#include <iostream>
using namespace std;

/*
    Divide el arreglo dado en dos recursivamente hasta llegar a arreglos de tamano uno. De ahi fusionar los arreglos y
    al fusionar sortear los numeros para que queden en orden.
*/

// Correr el algoritmoe de merge
void merge(vector<int>& arr, int left, int mid, int right){
    

}
// Correr el algoritmo de mergeSort
void mergeSort(vector<int>& arr, int left, int right){
    if(left < right) {
        int mid = left + (right-left)/2;    

        // Sort two halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid+1, right);

        // Merge Sorted halves
        merg(arr,left,mig,right);
    }
}

