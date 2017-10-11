#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>
using namespace std;


float logistic_func(float r, int n, float x0){
    if(n == 0) return x0;
    return r * logistic_func(r, n - 1, x0) * (1 - logistic_func(r, n - 1, x0));
}

int main(int argc, char** argv){
    float x0 = (float) atof(argv[1]);
    for(float r = 3.75; r <= 3.8; r += 0.0001)
        cout << r << "," << logistic_func(r, 20, x0) << endl;
}
