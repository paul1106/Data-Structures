#include<iostream>
#include<vector>
using namespace std;

vector<int> & SelectionSort(vector<int> &);

int main(){
    vector<int> vec;
    int num;
    while(cin >> num){
        vec.push_back(num);
    }

    SelectionSort(vec);

    for(auto c: vec){
        cout << c << " ";
    }
    cout << endl;
}


vector<int> & SelectionSort(vector<int> & vec){
    for(int i = 0; i < vec.size() - 1; i++){
        int min = i;
        for(int j = i + 1; j < vec.size(); j++){
            if(vec[j] < vec[min]){
                min = j;
            }
        }
        swap(vec[i], vec[min]);
    }

    return vec;
}

