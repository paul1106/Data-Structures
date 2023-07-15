#include<iostream>
#include<algorithm>
using namespace std;

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(int *arr, int front, int end){
    int pivot = arr[end];
    int i = front - 1; // 用來記錄比Pivot小的子陣列中最後一個值的Index
    for(int j = front; j < end; j++){
        if(arr[j] < pivot){
            i++;
            swap(&arr[j], &arr[i]);
        }
    }
    i++;
    swap(&arr[i], &arr[end]);
    return i;
}

void QuickSort(int *arr, int front, int end){
    if(front >= end) return; // 當給定的陣列的大小 <= 1
    int pivot = Partition(arr, front, end);
    Partition(arr, front, pivot - 1);
    Partition(arr, pivot + 1, end);
}

void PrintArray(int arr[], int n){
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main(){
    int n = 9;
    int arr[] = {9, 4, 1, 6, 7, 3, 8, 2, 5};
    PrintArray(arr, n);

    QuickSort(arr, 0, n - 1);
    PrintArray(arr, n);
    return 0;
}