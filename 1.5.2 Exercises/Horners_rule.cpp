#include<iostream>
#include<vector>
using namespace std;

double Horners_rule(vector<double>, double, double, double);

int main(){
    vector<double> vec;
    double tmp, x;
    cin >> x;
    while(cin >> tmp){
        vec.push_back(tmp);
    }
    double p = vec[0];

    cout << Horners_rule(vec, x, p, 1) << endl;
    return 0;
}

double Horners_rule(vector<double> vec, double x, double p, double i){
    // Evaluate a polynominal at a podouble Xo.
    if(i == vec.size())
        return p;
    else{
        p = p * x + vec[i++];
        cout << p << endl;
        return Horners_rule(vec, x , p, i);
    }
}