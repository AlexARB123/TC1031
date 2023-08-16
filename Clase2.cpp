#include <iostream>
using namespace std;

int factorial(int n);

int main(void){

    int x = factorial(5);
    cout << x;
}

int factorial(int n){
    
    if(n == 1){
        return 1;
    }

    return n * factorial(n-1);
}
