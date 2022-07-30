#include<iostream>
using namespace std;

int Factorial(int);

int main(){
    int n;
    cin >> n;
    cout << Factorial(n) << endl;
}

int Factorial(int n){
    if(n == 1){
        return 1;
    }else{
        return n * Factorial(n - 1);
    }
}