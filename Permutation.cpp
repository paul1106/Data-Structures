#include<iostream>
using namespace std;

void Permutation(string, const int, const int);

int main(){
    string str;
    cin >> str;
    Permutation(str, 0, str.size());

    return 0;
}

void Permutation(string str, const int k, const int m){
    // Generate all the Permutations of a[k], ... , a[m].
    if(k == m){
        for(int i = 0; i < m; i++){
            cout << str[i] << " ";
        }
        cout << endl;
    }else{
        // if there are more than one Permutations.
        for(int i = k; i < m; i++){
            swap(str[k], str[i]);
            Permutation(str, k + 1, m);
            swap(str[k], str[i]);
        }
    }
}
