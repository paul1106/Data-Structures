#include<iostream>
using namespace std;

int Multiplication(int, int);

int main(){
    int a, b;
    cin >> a >> b;
    cout << Multiplication(a, b) << endl;
}

int Multiplication(int a, int b){
    if(b == 1){
        return a;
    }else{
        return a + Multiplication(a, b - 1);
    }
}