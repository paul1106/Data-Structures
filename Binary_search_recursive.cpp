#include<iostream>
using namespace std;

int Binary_search(int *, const int, const int, const int);

int main(){
    int a[10];
    //輸入陣列
    for(int i = 0; i < 10; i++){
        int temp;
        cin >> temp;
        a[i] = temp;
    }

    int x;
    //target number
    cin >> x;

    cout << Binary_search(a, x, 0, 9) << endl;

    return 0;
}

int Binary_search(int *a, const int x, const int left, const int right){
    //Search the sorted array a[left], ... , a[right] for x
    if(left <= right){
        int middle = (left + right) / 2;
        if(x > a[middle]){
            return Binary_search(a, x, middle + 1, right);
        }else if(x < a[middle]){
            return Binary_search(a, x, left, middle - 1);
        }else{
            return middle;
        }
    }else{
        return -1;
    }    
}
