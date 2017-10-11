#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>
using namespace std;

int ns[] = { 50, 100, 200, 500, 1000};
double ss[] = {2, 3.6667, 5, 7.2, 10};



double dzeta(int n, double s, bool forward){
    if(forward) {
        double sum = 0.0;
        for(int k = 1; k <= n; k++)
            sum += 1 / pow(k, s);
        return sum;
    } else {
        double sum = 0.0;
        for(int k = n; k >= 1; k--)
            sum += 1 / pow(k, s);
        return sum;
    }
}

double eta(int n, double s, bool forward){
    if(forward) {
        double sum = 0.0;
        for(int k = 1; k <= n; k++){
            double sign = 1;
            if(k % 2 == 0)
                sign = -1;
            sum += sign / pow((double) k, s);
        }
        return sum;
    } else {
        double sum = 0.0;
        for(int k = n; k >= 1; k--){
            double sign = 1;
            if(k % 2 == 0)
                sign = -1;
            sum += sign / pow((double) k, s);
        }
        return sum;
    }
}

void double_forward() { 
    cout << "Forward: " << endl;

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cout << "Dzeta: " << "(n, i) = " << ns[i] << ", " << ss[j] << " -> " << dzeta(ns[i], ss[j], true) << endl;
            cout << "Eta " << "(n, i) = " << ns[i] << ", " << ss[j] << " -> " << eta(ns[i], ss[j], true) << endl;

        }
    }
}

void double_backward() { 
    cout << "Backward: " << endl;
    
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){

            cout << "Dzeta: " << "(n, i) = " << ns[i] << ", " << ss[j] << " -> " << dzeta(ns[i], ss[j], false) << endl;
            cout << "Eta " << "(n, i) = " << ns[i] << ", " << ss[j] << " -> " << eta(ns[i], ss[j], false) << endl;

        }
    }
}

int main(){
    
    double_forward();

}
