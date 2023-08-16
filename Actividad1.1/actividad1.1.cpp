/*
Alejandro Rodriguez del Bosque - A01722329
TC1031 - Programacion de estructuras de datos y algoritmos fundamentales
10 de Agosto 2023

Calcula la sumatoria de todos los numeros de 1 hasta n
utilizando metodos iterativos, recursivos y directos
*/

#include <iostream>
using namespace std;

// Declaracion de las funciones que se van a utilizar
int sumaIterativa(int sum);
int sumaRecursiva(int sum);
int sumaDirecta(int sum);

int main() {

  int testValue = -1;

  // Condicion de entrada de valor
  while (testValue <= 0){
    cout << "Ingrese un valor entero positivo" << endl;
    cin >> testValue;
    cout << endl;
  }

  int alt = sumaIterativa(testValue);
  int rec = sumaRecursiva(testValue);
  int dir = sumaDirecta(testValue);

  cout << "Alterativa: " << alt << endl;
  cout << "Recursiva: " << rec << endl;
  cout << "Directa: " << dir << endl;
}

/* 
* Calcula la suma de 1 hasta el numero deseado usando un metodo iterativo
*
*@Param (int sum) Valor deseado de la suma
*
*@return la suma de todos los valores de 1 a el valor deseado
*
*Complejidad de tiempo: O(n)
*Complejidad de espacio: O(1)
*/
int sumaIterativa(int sum) {
  int res = 0;

  // Se usa un for-loop para ir agregando numeros del i al sum. 
  for (int i = 0; i <= sum; i++) {
    res = res + i;
  }

  return res;
}

/* 
* Calcula la suma de 1 hasta el numero deseado usando recursion
*
*@Param (int sum) Valor deseado de la suma
*
*@return la suma de todos los valores de 1 a el valor deseado
*
*Complejidad de tiempo: O(n)
*Complejidad de espacio: O(n)
*/
int sumaRecursiva(int sum) {
  
  // Condicion de salida
  if(sum <= 0){ 
    return 0;
  }

  // Vuelve a llamar la funcion con un valor minimo, agregando del 1 hasta el n
  int res = sum + sumaRecursiva(sum - 1);

  return res;
}

/* 
* Calcula la suma de 1 hasta el numero deseado usando un metodo directo
*
*@Param (int sum) Valor deseado de la suma
*
*@return la suma de todos los valores de 1 a el valor deseado
*
*Complejidad de tiempo: O(1)
*Complejidad de espacio: O(1)
*/
int sumaDirecta(int sum){
  return (sum*(sum+1))/2;
}