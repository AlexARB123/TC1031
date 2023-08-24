#include <iostream>

using namespace std;

int encuentraNum(int nums[], int target);

int main(){
    int test[] = {0,4,3,6,5,10};
    int res = encuentraNum(test,11);
    cout << res;
}

int encuentraNum(int nums[], int target){
   
   for(int i = 0; i < sizeof(nums); i++){
        if(nums[i] == target){
            return i;
        }
   }
   return -1;
}