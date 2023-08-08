#include <iostream>
using namespace std;


// Este se utiliza para hacer funciones genericas
template<typename T>
	
	/* T representa un tipo de dato cualquiera, que tipo de dato es y que operacion realiza depende de
	los tipos que se llaman durante el llamado de la funcion*/
	
	T add(T arg1, T arg2){
	return arg1 + arg2;
}

int main() {
	int ans = add(1, 2);
	cout << ans << endl;

	float checl = add(1.5,3.57);
	string a = "Hello, ";
	string b = "World";

	string c = add(a,b);


	cout << checl << endl;

	cout << c << endl;
}