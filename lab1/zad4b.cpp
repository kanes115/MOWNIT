#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>
using namespace std;


double logistic_func(double r, int n, double x0){
    if(n == 0) return x0;
    return r * logistic_func(r, n - 1, x0) * (1 - logistic_func(r, n - 1, x0));
}

double iterate_double(double r, double x){
    return r*x*(1-x);
}

double iterating_double(double r, double x, int n){
    for(int i = 0; i <n ;i++)
        x = iterate_double(r, x);
    return x;
}

int main(int argc, char** argv){
    double x0 = (double) atof(argv[1]);
    for(double r = 3.75; r <= 3.8; r += 0.0001)
        for(int xn = 1; xn < 1000; xn++)
            cout << r << "," << iterating_double(r, x0, xn) << endl;
}
