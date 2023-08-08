/*
Alejandro Rodriguez del Bosque - A01722329
TC1031 - Programacion de estructuras de datos y algoritmos fundamentales
Actividad 1.1
*/

#include <iostream>
using namespace std;

// Declaracion de las funciones que se van a utilizar
int sumaAlterativa(int sum);
int sumaRecursiva(int sum);
int sumaDirecta(int sum);

// Metodo main para correr los datos y casos de prueba
int main() {

  int testValue = -1;

  // Condicion de entrada de valor
  while (testValue <= 0){
    cout << "Ingrese un valor entero positivo" << endl;
    cin >> testValue;
    cout << endl;
  }

  int alt = sumaAlterativa(testValue);
  int rec = sumaRecursiva(testValue);
  int dir = sumaDirecta(testValue);

  cout << "Alterativa: " << alt << endl;
  cout << "Recursiva: " << rec << endl;
  cout << "Directa: " << dir << endl;
}

int sumaAlterativa(int sum) {
  int res = 0;

  // Se usa un for-loop para ir agregando numeros del i al sum. 
  for (int i = 0; i <= sum; i++) {
    res = res + i;
  }

  return res;
}

int sumaRecursiva(int sum) {
  // Condicion de salida
  if(sum <= 0){
    return 0;
  }

  // Vuelve a llamar la funcion con un valor minimo, agregando del 1 hasta el n
  int res = sum + sumaRecursiva(sum - 1);

  return res;
}

int sumaDirecta(int sum){
  // Usa la formula (n*[n+1])/2 = x para calcular el valor final
  return (sum*(sum+1))/2;
}