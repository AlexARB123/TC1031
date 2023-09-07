#include <iostream>

using namespace std;

int encuentraNum(int nums[], int target);
int recEncuentraNum(int nums[], int target, int start);
int busquedaBinaria(int nums[], int target, int size);
int recBusquedaBinaria(int nums[], int target, int left, int right);
int first(int nums[], int low, int high, int key);
int last(int nums[], int low, int high, int key);
int total(int nums[], int low, int high, int key);

int main(){
    int test[] = {0,4,3,6,5,10};
    int size = sizeof(test) / sizeof(test[0]);
    int res = encuentraNum(test,3);
    int resR = recEncuentraNum(test,3,size);
    cout << "Busqueda Lineal: " << endl << res;
    cout << endl << resR << endl;

    int test2[] = {0,1,2,3,4,5,6,7,8,9,10};
    int size2 = sizeof(test2) / sizeof(test2[0]);
    int res2 = busquedaBinaria(test2,5, size2);
    int res2R = recBusquedaBinaria(test2,5, 0, size2);
    cout << "Busqueda Binaria" << endl << res2 << endl;
    cout << res2R << endl;

    int test3[] = {0,1,1,1,1,1,1,1,6};
    int size3 = sizeof(test3) / sizeof(test3[0]);
    int res3 = first(test3, 0, size3, 1);
    int res3L = last(test3,0,size3,1);
    int res3T = total(test3,0,size3,1);
    cout << "Primera instancia : " << res3 << endl;
    cout << "Ultima instancia : " << res3L << endl; 

    cout << "Total: " << res3T;

}
/*
* Encuentra linealmente de manera iterativa el indice de un numero encontrado en un array
*
*@Param - (int nums[]) lista de numeros donde buscar (int target) el numero a buscar
*
*@return - indice del numero encontrado o -1
*/
int encuentraNum(int nums[], int target){
   
   for(int i = 0; i < sizeof(nums); i++){
        if(nums[i] == target){
            return i;
        }
   }
   return -1;
}

/*
* Encuentra linealmente de manera recursiva el indice de un numero encontrado en un array
*
*@Param - (int nums[]) lista de numeros donde buscar (int target) el numero a buscar (int size) - tamano del arreglo
*
*@return - indice del numero encontrado o -1
*/
int recEncuentraNum(int nums[], int target, int size){
    if(size == 0){
        return -1;
    }

    else if(target == nums[size-1]){
        return size-1;
    }
    else{

        int ans = recEncuentraNum(nums,target, size-1);
        return ans;
    }
    
}

int busquedaBinaria(int nums[], int target, int size){
    int left = 0;
    int right = size;
    int answer = -1;

    while(true){
        if(left >= right){
            return -1;
        }

        int Index = left + ((left + right)/2);

        if(nums[Index] == target){
            return Index;
        }
        else if(nums[Index] > target){
            right = Index - 1;
        }
        else if(nums[Index] < target){
            left = Index + 1;
        }
    }
}
int recBusquedaBinaria(int nums[], int target, int left, int right){
    
    if(left >= right){
        return -1;
    }

    int Index = left + ((left + right)/2); 

    if (nums[Index] == target){
        return Index;
    }
    else if(nums[Index] > target){
        return recBusquedaBinaria(nums,target,left, (Index-1));
    }
    else if(nums[Index] < target){
        return recBusquedaBinaria(nums,target,(Index+1), right);
    }
    return -1;
}

int first(int nums[], int low, int high, int key)
{
    int ans = -1;
 
    while (low <= high) {
        int mid = low + (high - low + 1) / 2;
        int midVal = nums[mid];
 
        if (midVal < key) {
 
            // if mid is less than key, all elements
            // in range [low, mid] are also less
            // so we now search in [mid + 1, high]
            low = mid + 1;
        }
        else if (midVal > key) {
 
            // if mid is greater than key, all elements
            // in range [mid + 1, high] are also greater
            // so we now search in [low, mid - 1]
            high = mid - 1;
        }
        else if (midVal == key) {
 
            // if mid is equal to key, we note down
            //  the last found index then we search
            // for more in left side of mid
            // so we now search in [low, mid - 1]
            ans = mid;
            high = mid - 1;
        }
    }
 
    return ans;
}

int last(int nums[], int low, int high, int key)
{
    int ans = -1;
 
    while (low <= high) {
        int mid = low + (high - low + 1) / 2;
        int midVal = nums[mid];
 
        if (midVal < key) {
 
            // if mid is less than key, all elements
            // in range [low, mid] are also less
            // so we now search in [mid + 1, high]
            low = mid + 1;
        }
        else if (midVal > key) {
 
            // if mid is greater than key, all elements
            // in range [mid + 1, high] are also greater
            // so we now search in [low, mid - 1]
            high = mid - 1;
        }
        else if (midVal == key) {
 
            // if mid is equal to key, we note down
            //  the last found index then we search
            // for more in left side of mid
            // so we now search in [low, mid - 1]
            ans = mid;
            low = mid + 1;
        }
    }
 
    return ans;
}

int total(int nums[], int low, int high, int key){
    int answer = 0;

    int top = last(nums,low,high,key);
    int bottom = first(nums,low,high,key);

    if(top  < 0 || bottom < 0){
        return answer;
    }

    answer = top - bottom;
    return answer;
}