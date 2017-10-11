#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>
using namespace std;


float logistic_func(float r, int n, float x0){
    if(n == 0)
        return x0;
    float log_val = logistic_func(r, n - 1, x0);
    return r * log_val * (1 - log_val);
}

int main(int argc, char** argv){
    cout << "x0,counter" << endl;
    for(float x0 = 0.1; x0 <= 0.9; x0 += 0.00001){
        for(int n = 1; n < 100; n ++){
            if(abs(logistic_func(4, n, x0)) < 0.00001){
                cout << x0 << "," <<  n << endl;
                break;
            }
        }
    }
}
