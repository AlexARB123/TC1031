#include <iostream>
#include <vector>
using namespace std;


void insertionSort(vector<int>& arr){
    
    int n = arr.size();

    for(int i = 1; i < n; i++){
        int key = arr[i];
        int j = i-1;

        while(j >= 0 && arr[j] > key){
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;
    }
}

int main(){
    
    vector<int> test = {1,4,2,3,6,12,4,2,3,21,32,43,51,12,34,11};
    insertionSort(test);
    for(int i = 0; i < test.size(); i++){
        cout << test[i] << " ";
    }
}