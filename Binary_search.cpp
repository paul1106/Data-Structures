#include<iostream>
#include<vector>
using namespace std;

void Binary_search(vector<int> &, int, int, int);

int main(){
    int n, num;
    vector<int> vec;

    //n 紀錄陣列大小, num 紀錄要找的數
    cin >> n >> num;
    for(int i = 0; i < n; i++){
        int tmp;
        cin >> tmp;
        vec.push_back(tmp);
    }

    Binary_search(vec, num, 0, vec.size() - 1);
    return 0;
}

void Binary_search(vector<int> & vec, int num, int left, int right){
    int mid = (left + right) / 2;
    //沒找到這個數字

    if(right < left){
        cout << "not found" << endl;
        return;
    }else if(num == vec[mid]){
        cout << mid << endl;
        return;
    }else if(num > vec[mid]){
        Binary_search(vec, num, mid + 1, right);
    }else{
        Binary_search(vec, num, left, mid - 1);
    }
}