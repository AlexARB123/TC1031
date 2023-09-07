#include <iostream>
#include <vector>
using namespace std;


int hoarePartition(vector<int>& arr, int low, int high){
    int pivot = arr[low];
    int i = low-1;
    int j = high + 1;

    while(true){
        do{
            i++;
        }while(arr[i] < pivot);

        do{
            j--;
        } while (arr[j] > pivot);

        if(i >= j){
            return j;
        }

        swap(arr[i], arr[j]);
    }
}
int partition(vector<int>& arr, int low, int high){
    int pivot = arr[high];
    int i = low - 1;
    
    for(int j = low; j <= high; j++){
        if(arr[j] <= pivot){
            i++;
            swap(arr[i],arr[j]);
        }
    }

    swap(arr[i+1], arr[high]);

    return i+1;
}

void quickSort(vector<int>& arr, int low, int high){
    if (low < high){
        int pivotIndex = hoarePartition(arr,low,high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}


int main(){
    vector<int> test = {1,4,12,45,2,33,465,1,23,51,23,5,12355,614,3612,10};

    quickSort(test, 0 , test.size());

    for(int i = 0; i < test.size(); i++){
        cout << test[i] << " ";
    }
}